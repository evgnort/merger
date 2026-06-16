#include <stdlib.h>

#include "parser.h"
#include "codeseq.h"

int make_sorted_regs_rps(int tick,int count, int *regs, double *target)
   {
   int i;
   int ucnt = 0;
   for (i = 0; i < count; i++)
      {
      double val = (regs[i] && regs[i] > tick) ? 1.0 / (regs[i] - tick) : 0;
      int pos = i;  
      while (pos > 0 && target[pos - 1] < val)
         {
         target[pos] =  target[pos - 1];
         pos--;
         };
      target[pos] = val;
      if (val)
         ucnt++;
      }
   return ucnt;
   }

void update_port_usage_pmf(FTickPortUsage *target,double prob)
   {
   int i;
   
   for (i = MAX_PORT_PRESSURE - 2; i >= 0; i--)
      {
      target->probs[i + 1] += target->probs[i] * prob;
      target->probs[i] *= (1 - prob);
      }
   }

FTickSet *make_tick_seq(FInstructionSet *is)
   {
   int port;
   int i,j,k;

   int max_size = is->instructions[is->inst_cnt - 1].tick + MAX_LATENCY;

   FTickSet *rv = (FTickSet *)malloc(sizeof(FTickSet) + sizeof(FTick) * max_size);
   rv->ticks_count = 0;
   FTick *tick = rv->ticks;

   for (i = 0; i < max_size; i++)
      for (j = 0; j < PORTS_COUNT; j++)
         tick[i].ports[j].probs[0] = 1.0;
      
   for (i = REG_RAX; i < REG_YMM0; i++)
      for (j = 0; j < is->reg_initial_usage[i]; j++)
         tick[j].regs[SCALAR_REGS].reg_rd[i] = is->reg_initial_usage[i];

   for (i = REG_YMM0; i < REG_MAX; i++)
      for (j = 0; j < is->reg_initial_usage[i]; j++)
         tick[j].regs[VECTOR_REGS].reg_rd[i - REG_YMM0] = is->reg_initial_usage[i];

   for (k = 0; k < is->inst_cnt; k++)
      {
      for (i = REG_RAX; i < REG_YMM0; i++)
         {
         for (j = is->instructions[k].tick + 1; j < is->instructions[k].reg_next_usage[i]; j++)
            tick[j].regs[SCALAR_REGS].reg_rd[i] = is->instructions[k].reg_next_usage[i];
         }

      for (i = REG_YMM0; i < REG_MAX; i++)
         {
         for (j = is->instructions[k].tick + 1; j < is->instructions[k].reg_next_usage[i]; j++)
            tick[j].regs[VECTOR_REGS].reg_rd[i - REG_YMM0] = is->instructions[k].reg_next_usage[i];
         }

      int mt = is->instructions[k].tick;
      tick[mt].sline = is->instructions[k].line;
      for (i = 0; i < is->instructions[k].latency; i++)
         tick[mt + i].sline = is->instructions[k].line;
      if (mt + i > rv->ticks_count)
         rv->ticks_count = mt + i;

      for (i = 0; i < is->instructions[k].mops_cnt; i++)
         {
         double prob = 1.0 / __builtin_popcount(is->instructions[k].ops[i].portmask);
 
         for (port = 0; port < 8; port++)
            {
            if ((1 << port) & is->instructions[k].ops[i].portmask)
               {
               for (j = 0; j < is->instructions[k].ops[i].duration; j++)
                  update_port_usage_pmf(&tick[mt + j].ports[port],prob);
               }
            }
         if (!(is->instructions[k].ops[i].flags & MOP_UNCHAINED))
            mt += is->instructions[k].ops[i].latency;
         }
      }

   for (port = 0; port < PORTS_COUNT; port++)
      {
      for (i = 0; i <= rv->ticks_count; i++)
         {
         double vals[MAX_PORT_PRESSURE] = {0};
         for (k = 0; k < AVG_WINDOW; k++)
            for (j = 0; j < MAX_PORT_PRESSURE; j++)
               vals[j] += tick[i + k].ports[port].probs[j];

         for (j = 0; j < MAX_PORT_PRESSURE; j++)
            tick[i].ports[port].probs[j] = vals[j] / AVG_WINDOW;
         }
      }

   for (i = 0; i <= rv->ticks_count; i++)
      {
      tick[i].regs[SCALAR_REGS].reg_cnt = make_sorted_regs_rps(i,16,tick[i].regs[SCALAR_REGS].reg_rd,tick[i].regs[SCALAR_REGS].reg_rp_sorted);
      tick[i].regs[VECTOR_REGS].reg_cnt = make_sorted_regs_rps(i,16,tick[i].regs[VECTOR_REGS].reg_rd,tick[i].regs[VECTOR_REGS].reg_rp_sorted);
//      printf("%d %d %d\n",i,tick[i].regs[SCALAR_REGS].reg_cnt,tick[i].regs[VECTOR_REGS].reg_cnt);
//      printf("%d %.2f %.2f %.2f %.2f\n",i,tick[i].ports[5].probs[0],tick[i].ports[5].probs[1],tick[i].ports[5].probs[2],tick[i].ports[5].probs[3]);
      }
   return rv;
   }

FTimeline *make_timeline(FTickSet *ts)
   {
   int i,j,k;  
   FTimeline *rv = (FTimeline *)malloc(sizeof(FTimeline));
   double *work_arr = (double *)malloc(sizeof(double) * PORTS_COUNT * MAX_PORT_PRESSURE * ts->ticks_count);

   rv->size = ts->ticks_count;
   for (i = 0; i < PORTS_COUNT; i++)
      for (j = 0; j < MAX_PORT_PRESSURE; j++)
         {
         rv->ports_usage[i][j] = work_arr;
         for (k = 0; k < rv->size; k++)
            work_arr[k] = ts->ticks[k].ports[i].probs[j];
         work_arr += rv->size;
         }

   work_arr = (double *)malloc(sizeof(double) * REG_SETS_COUNT * REGS_COUNT * ts->ticks_count);
   for (i = 0; i < REG_SETS_COUNT; i++)
      for (j = 0; j < REGS_COUNT; j++)
         {
         rv->regs_usage[i][j] = work_arr;
         for (k = 0; k < rv->size; k++)
            work_arr[k] = ts->ticks[k].regs[i].reg_rp_sorted[j];
         work_arr += rv->size;
         }
   return rv;
   }

void free_timeline(FTimeline *tl)
   {
   free(tl->ports_usage[0][0]);
   free(tl->regs_usage[0][0]);
   free(tl);
   }

int portset2num[256] = { 0 };
int num2portset[PORT_SETS_COUNT] = { 0 };
const char *portset_names[PORT_SETS_COUNT] = { "p0","p1","p2","p3","p4","p5","p6","p7","p01","p015","p0156","p06","p15","p23","p237",""};

void init_port_sets(void)
   {
   num2portset[0] = PORT_0;
   num2portset[1] = PORT_1;
   num2portset[2] = PORT_2;
   num2portset[3] = PORT_3;
   num2portset[4] = PORT_4;
   num2portset[5] = PORT_5;
   num2portset[6] = PORT_6;
   num2portset[7] = PORT_7;

   num2portset[8] = PORT_01;
   num2portset[9] = PORT_015;
   num2portset[10] = PORT_0156;
   num2portset[11] = PORT_06;
   num2portset[12] = PORT_15;
   num2portset[13] = PORT_23;
   num2portset[14] = PORT_237;
   num2portset[15] = 0;

   portset2num[PORT_0] = 0;
   portset2num[PORT_1] = 1;
   portset2num[PORT_2] = 2;
   portset2num[PORT_3] = 3;
   portset2num[PORT_4] = 4;
   portset2num[PORT_5] = 5;
   portset2num[PORT_6] = 6;
   portset2num[PORT_7] = 7;

   portset2num[PORT_01] = 8;
   portset2num[PORT_015] = 9;
   portset2num[PORT_0156] = 10;
   portset2num[PORT_06] = 11;
   portset2num[PORT_15] = 12;
   portset2num[PORT_23] = 13;
   portset2num[PORT_237] = 14;
   }

int get_portset_by_num(int psnum)
   {
   return num2portset[psnum];
   }

const char *get_psname_by_num(int psnum)
   {
   return portset_names[psnum];
   }

typedef struct FMOpsDescTg {
   int tick;
   uint32_t portmask;
   uint32_t duration;
   } FMOpsDesc;

int compare_mops(const void *a,const void *b)
   {
   FMOpsDesc *s1 = (FMOpsDesc *)a;
   FMOpsDesc *s2 = (FMOpsDesc *)b; 
   if (s1->tick > s2->tick)
      return 1;
   if (s1->tick < s2->tick)
      return -1;
   return 0;
   }

FSeqAggregate *make_seq_aggregate(FInstructionSet *is)
   {
   FMOpsDesc mopsdesc[2048];
   int sreg_usage[2048][REGS_COUNT] = {0};
   int vreg_usage[2048][REGS_COUNT] = {0};
   int cnt = 0, lat_cnt = 0;

   int i,j,k;
   double lat_sum = 0;
   double lat_sum2 = 0;

   FSeqAggregate *rv = (FSeqAggregate *)calloc(1,sizeof(FSeqAggregate));

   double TSum = 0;
   double pES2[PORT_SETS_COUNT] = {0};

   for (i = REG_RAX; i < REG_YMM0; i++)
      for (j = 0; j < is->reg_initial_usage[i]; j++)
         sreg_usage[j][i] = is->reg_initial_usage[i];

   for (i = REG_YMM0; i < REG_MAX; i++)
      for (j = 0; j < is->reg_initial_usage[i]; j++)
         vreg_usage[j][i - REG_YMM0] = is->reg_initial_usage[i];

   for (k = 0; k < is->inst_cnt; k++)
      {
      for (i = REG_RAX; i < REG_YMM0; i++)
         {
         for (j = is->instructions[k].tick + 1; j < is->instructions[k].reg_next_usage[i]; j++)
            sreg_usage[j][i] = is->instructions[k].reg_next_usage[i];
         }

      for (i = REG_YMM0; i < REG_MAX; i++)
         {
         for (j = is->instructions[k].tick + 1; j < is->instructions[k].reg_next_usage[i]; j++)
            vreg_usage[j][i - REG_YMM0] = is->instructions[k].reg_next_usage[i];
         }
      }

   int itick = 0;
   for (k = 0; k < is->inst_cnt; k++)
      {
      itick = is->instructions[k].tick;
      for (i = 0; i < is->instructions[k].mops_cnt; i++)
         {
         mopsdesc[cnt].tick = itick;
         mopsdesc[cnt].portmask = is->instructions[k].ops[i].portmask;
         mopsdesc[cnt].duration = is->instructions[k].ops[i].duration;
         if (!is->instructions[k].ops[i].flags & MOP_UNCHAINED)
            {
            double ml = is->instructions[k].ops[i].latency;
            lat_sum += ml;
            lat_sum2 += ml * ml;
            lat_cnt++;
            itick += is->instructions[k].ops[i].latency;
            }
         cnt++;
         }
      }
   rv->EZ = lat_sum / lat_cnt;
   double EZ2 =  rv->EZ * rv->EZ;
   rv->CZ2 = (lat_sum2 / lat_cnt - EZ2) / EZ2;

   for (i = 0 ; i < itick; i++)
      {
      int ucnt = 0;
      for (j = 0; j < REGS_COUNT; j++)
         ucnt += (sreg_usage[i][j] && sreg_usage[i][j] > i);
      rv->sregs_pmf[ucnt] += 1.0;

      ucnt = 0;
      for (j = 0; j < REGS_COUNT; j++)
         ucnt += (vreg_usage[i][j] && vreg_usage[i][j] > i);
      rv->vregs_pmf[ucnt] += 1.0;
      }

   for (j = 0; j < REGS_COUNT; j++)
      {
      rv->sregs_pmf[j] /= itick;
      rv->vregs_pmf[j] /= itick;
      }

   qsort(mopsdesc,cnt,sizeof(FMOpsDesc),compare_mops);

   for (i = 0; i < cnt; i++)
      {
      int psnum = portset2num[mopsdesc[i].portmask];
      double dur = mopsdesc[i].duration;
      TSum += dur;
      rv->portsets[psnum].ES += dur;
      pES2[psnum] += dur * dur;
      rv->portsets[psnum].use_count++;
      }

   rv->T = rv->EZ + TSum / cnt;
   rv->size = itick;

   rv->size = (double)itick / rv->T;

   for (i = 0; i < PORT_SETS_COUNT ; i++)
      {
      if (!rv->portsets[i].use_count)
         continue;
      rv->portsets[i].ES /= rv->portsets[i].use_count;
      rv->portsets[i].usage = (double)rv->portsets[i].use_count / rv->size;
      double ES2 =  rv->portsets[i].ES * rv->portsets[i].ES;
      rv->portsets[i].CS2 = (pES2[i] / rv->portsets[i].use_count - ES2) / ES2;
      }

   return rv;
   }