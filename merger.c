#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#include "fft.h"
#include "parser.h"
#include "codeseq.h"
#include "merger.h"

float merge_regs_direct_full(const FTickSet *ts1, const FTickSet *ts2, int shift, int reg_type)
   {
   int i,j,k;
   int start = (shift > 0) ? shift : 0;
   int end = (ts1->ticks_count < ts2->ticks_count + shift) ? ts1->ticks_count : (ts2->ticks_count + shift);

   float penalty = 0;

   int *rd1r = (int *)malloc(ts1->ticks_count * sizeof(int) * REGS_COUNT);
   int *rd1c = (int *)malloc(ts1->ticks_count * sizeof(int));
   int *rd2r = (int *)malloc(ts2->ticks_count * sizeof(int) * REGS_COUNT);
   int *rd2c = (int *)malloc(ts2->ticks_count * sizeof(int));

   for (i = 0 ; i < ts1->ticks_count; i++)
      {
      rd1c[i] = ts1->ticks[i].regs[reg_type].reg_cnt;
      for (j = 0; j < REGS_COUNT; j++)
         rd1r[i * REGS_COUNT + j] = ts1->ticks[i].regs[reg_type].reg_rd[j];
      }

   for (i = 0 ; i < ts2->ticks_count; i++)
      {
      rd2c[i] = ts2->ticks[i].regs[reg_type].reg_cnt;
      for (j = 0; j < REGS_COUNT; j++)
         rd2r[i * REGS_COUNT + j] = ts2->ticks[i].regs[reg_type].reg_rd[j];
      }

   for (i = start; i < end; i++)
      {
      int i2 = i - shift;
      int rusage = rd1c[i] + rd2c[i2];
      if (rusage <= REGS_COUNT)
         continue;

      penalty += (rusage -= REGS_COUNT);
      for (k = 0; k < rusage; k++)
         {
         int *targ_r = NULL, *targ_c = NULL;
         int md = 0;
         for (j = 0; j < REGS_COUNT; j++)
            {
            if (rd1r[i * REGS_COUNT + j] && rd1r[i * REGS_COUNT + j] - i > md)
               {
               targ_r = &rd1r[i * REGS_COUNT + j];
               targ_c = &rd1c[i];
               md = rd1r[i * REGS_COUNT + j] - i;
               }
            if (rd2r[i2 * REGS_COUNT + j] && rd2r[i2 * REGS_COUNT + j] - i2 > md)
               {
               targ_r = &rd2r[i2 * REGS_COUNT + j];
               targ_c = &rd2c[i2];
               md = rd2r[i2 * REGS_COUNT + j] - i2;
               }
            }
         for (j = 0; j < md; j++)
            {
            (*targ_c)--;
            (*targ_r) = 0;
            targ_c++;
            targ_r += REGS_COUNT;
            }
         }
      }
   free(rd1c);
   free(rd1r);
   free(rd2c);
   free(rd2r);
   return penalty;
   }

float merge_regs_direct_light(FTickSet *ts1, FTickSet *ts2, int shift, int reg_type)
   {
   int i,j;
   int start = (shift > 0) ? shift : 0;
   int end = (ts1->ticks_count < ts2->ticks_count + shift) ? ts1->ticks_count : (ts2->ticks_count + shift);

   float penalty = 0;
   for (i = start; i < end; i++)
      {
      int i2 = i - shift;
      int rusage = ts1->ticks[i].regs[reg_type].reg_cnt + ts2->ticks[i2].regs[reg_type].reg_cnt;
      if (rusage > 16)
         {
         int mp = ts1->ticks[i].regs[reg_type].reg_cnt - 1;
         for (j = 0; j < rusage - 16; j++)
            penalty += ts1->ticks[i].regs[reg_type].reg_rp_sorted[mp - j];
         }
      }
   return penalty;
   }

float merge_ports_direct(FTickSet *ts1, FTickSet *ts2, int shift, int port)
   {
   int i,j,k;
   int start = (shift > 0) ? shift : 0;
   int end = (ts1->ticks_count < ts2->ticks_count + shift) ? ts1->ticks_count : (ts2->ticks_count + shift);

   float penalty = 0;
   for (i = start; i < end; i++)
      {
      int i2 = i - shift;
      for (j = 0; j < MAX_PORT_PRESSURE; j++)
         for (k = 0; k < MAX_PORT_PRESSURE; k++)
            {
            if (j + k <= 1)
               continue;
            penalty += (j + k - 1) * ts1->ticks[i].ports[port].probs[j] * ts2->ticks[i2].ports[port].probs[k];
            }
      }
   return penalty;
   }

double *timelines_port_merge(FTimeline *tl1, FTimeline *tl2)
   {
   int i,j,k;
   int rsize = get_result_size(tl1->size,tl2->size);
   double complex *sp1all = (double complex *)malloc(sizeof(double complex) * rsize * MAX_PORT_PRESSURE);
   double complex *sp2all = (double complex *)malloc(sizeof(double complex) * rsize * MAX_PORT_PRESSURE);
   double complex *res = (double complex *)malloc(sizeof(double complex) * rsize * 2);
   double complex *ressum = &res[rsize];

   double complex *sp1[MAX_PORT_PRESSURE];
   double complex *sp2[MAX_PORT_PRESSURE];

   double *penalties = calloc(rsize,sizeof(double));
   double *pensum = calloc(rsize,sizeof(double));

   for (j = 0; j < MAX_PORT_PRESSURE; j++)
      {
      sp1[j] = &sp1all[rsize * j];
      sp2[j] = &sp2all[rsize * j];
      }

   for (i = 0; i < PORTS_COUNT; i++)
      {
      for (j = 0; j < MAX_PORT_PRESSURE; j++)
         {
         fft1d(tl1->ports_usage[i][j],tl1->size,sp1[j],rsize);
         fft1d(tl2->ports_usage[i][j],tl2->size,sp2[j],rsize);
         }

      memset(ressum,0,sizeof(double complex) * rsize);
      for (j = 0; j < MAX_PORT_PRESSURE; j++)
      for (k = 0; k < MAX_PORT_PRESSURE; k++)
         {
         if (j + k <= 1) continue;
         cc_multiply(sp1[j],sp2[k],res,rsize);
         c_add(ressum,res,(double)(j + k - 1),rsize);
         }
      ifft_doubles(ressum,penalties,rsize);

      for (j = 0; j < rsize; j++)
         pensum[j] += penalties[j];
      }
//   for (j = 0; j < rsize; j++)
//      printf("%d: %f\n",j,pensum[j]);

   free(penalties);
   return pensum;
   }

double *timelines_regs_merge(FTimeline *tl1, FTimeline *tl2, int reg_type)
   {
   int rsize = get_result_size(tl1->size,tl2->size);
	return NULL;
   }

#define INSTS_CNT_MAX 256

int main(int argc, char *argv[]) 
   {
   FInstructionSet *is1 = NULL, *is2 = NULL;
   FTickSet *ts1 = NULL, *ts2 = NULL;
   FTimeline *tl1 = NULL,*tl2 = NULL;

   if (argc != 3)
      return puts("format: ./merger file1.s file2.s"),0;
	
	char *fname1 = argv[1];
	char *fname2 = argv[2];
   
   int i;
  
   parser_init();
   init_fft();

   is1 = parser_read_file(fname1);
   if (!is1)
      goto main_exit;
   ts1 = make_tick_seq(is1);
   if (!ts1)
      goto main_exit;

   is2 = parser_read_file(fname2);
   if (!is2)
      goto main_exit;
   ts2 = make_tick_seq(is2);
   if (!ts2)
      goto main_exit;


   tl1 = make_timeline(ts1);
   if (!tl1)
      goto main_exit;
   tl2 = make_timeline(ts2);
   if (!tl2)
      goto main_exit;

   timelines_port_merge(tl1,tl2); 
   timelines_regs_merge(tl1,tl2,SCALAR_REGS);
   timelines_regs_merge(tl1,tl2,VECTOR_REGS);

   int shift;
   int bestshift = ts1->ticks_count;
   int seqlen = ts1->ticks_count + ts2->ticks_count;
   float bestres = seqlen;
   float bestregs = 0, bestports = 0;
   int minlen = (ts1->ticks_count > ts2->ticks_count) ? ts1->ticks_count : ts2->ticks_count;

   for (shift = -ts2->ticks_count + 1; shift < ts1->ticks_count; shift++)
      {
      int len;
      if (shift < 0)
         len = (ts1->ticks_count - shift > ts2->ticks_count) ? ts1->ticks_count - shift : ts2->ticks_count;
      else
         len = (ts2->ticks_count + shift > ts1->ticks_count) ? ts2->ticks_count + shift : ts1->ticks_count;

      float rp1 = merge_regs_direct_full(ts1,ts2,shift,SCALAR_REGS);
      float rp2 = merge_regs_direct_full(ts1,ts2,shift,VECTOR_REGS);

      float pp = 0;
      for (i = 0; i < 8; i++)
         pp += merge_ports_direct(ts1,ts2,shift,i);

      float wt1 = REG_PENALTY * (rp1 + rp2);
      float wt2 = PORT_PENALTY * pp;
      float wt = wt1 + wt2 + (len - minlen);
      printf("%4d: %.3f, %.3f, %.3f = %.3f + %d\n",shift,rp1,rp2,pp,REG_PENALTY * (rp1 + rp2) + PORT_PENALTY * pp,(len - minlen));
      if (wt < bestres)
         {
         bestshift = shift;
         bestres = wt;
         bestregs = wt1;
         bestports = wt2;
         }
      }
   printf("Sequental: %d\n",seqlen);
   if (bestshift < 0)
      printf("Best:  %.f shift %d (%s line %d) (ports: %.f + regs: %.f + lenght: %.f)\n",minlen + bestres,-bestshift,fname2,ts2->ticks[-bestshift].sline,bestports,bestregs,bestres - bestports - bestregs);
   else
      printf("Best:  %.f shift %d (%s line %d) (ports: %.f + regs: %.f + lenght: %.f)\n",minlen + bestres,bestshift,fname1,ts1->ticks[bestshift].sline,bestports,bestregs,bestres - bestports - bestregs);

main_exit:
   if (tl1) free_timeline(tl1);
   if (tl2) free_timeline(tl2);
   if (ts1) free(ts1);
   if (ts2) free(ts2);
   if (is1) free(is1);
   if (is2) free(is2);
   return 0;
   }


