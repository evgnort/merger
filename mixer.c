#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "codeseq.h"

FSeqBlock *known_blocks[1 << SEQ_NUM_COUNT];

FSeqBlock * make_block(uint32_t seqmask,FSeqAggregate **seqs)
   {
   FSeqBlock *block = (FSeqBlock *)calloc(1,sizeof(FSeqBlock));
   int pset,seqnum,seqnum2,i,j;

   block->seqmask = seqmask;
   block->seqcount = __builtin_popcount(seqmask);

   block->TD = 0;

   int mseq = __builtin_ctz(seqmask);

   double sreg_prob = 0;
   double vreg_prob = 0;

   if (block->seqcount == 1)
      {
      memcpy(block->sregs_pmf,seqs[mseq]->sregs_pmf,sizeof(double) * REGS_COUNT);
      memcpy(block->vregs_pmf,seqs[mseq]->vregs_pmf,sizeof(double) * REGS_COUNT);
      }
   else
      {
      FSeqBlock *prevblock = known_blocks[seqmask - (1 << mseq)];
      for (i = 0; i < REGS_COUNT; i++)
      for (j = 0; j < REGS_COUNT; j++)
         {
         block->sregs_pmf[i + j] += seqs[mseq]->sregs_pmf[i] * prevblock->sregs_pmf[j];
         block->vregs_pmf[i + j] += seqs[mseq]->vregs_pmf[i] * prevblock->vregs_pmf[j];
         }
      for (i = 0; i < REGS_COUNT; i++)
         {
         sreg_prob += block->sregs_pmf[i];
         vreg_prob += block->vregs_pmf[i];
         }
      sreg_prob = 1.0 - sreg_prob;
      vreg_prob = 1.0 - vreg_prob;
      }

   for (seqnum = 0; seqnum < SEQ_NUM_COUNT; seqnum++)
      {
      if (!(seqmask & (1 << seqnum)))
         continue;

      FSeqAggregate *agg = seqs[seqnum];
      FSeqBlock *prevblock = known_blocks[seqmask - (1 << seqnum)];

      int agg_psets[PORT_SETS_COUNT] = {0};
      int agg_psetscnt = 0;
      for (pset = 0; pset < PORT_SETS_COUNT; pset++)
         if (agg->portsets[pset].usage)
            agg_psets[agg_psetscnt++] = pset;

      double T = agg->EZ;
      double R[PORT_SETS_COUNT] = {0};
      for (i = 0; i < agg_psetscnt; i++)
         {
         pset = agg_psets[i];
         int pmask = get_portset_by_num(pset);

         double seqWeights[SEQ_NUM_COUNT] = {0};

         seqWeights[seqnum] = agg->portsets[pset].usage / agg->T;

         double swsum = seqWeights[seqnum];
         double ro = seqWeights[seqnum] * agg->portsets[pset].ES;
         if (prevblock)
            {
            double ro_mult = (agg->T * agg->size) / prevblock->TD;
            ro *= ro_mult;
            for (seqnum2 = 0; seqnum2 < SEQ_NUM_COUNT; seqnum2++)
               if (prevblock->seqmask & (1 << seqnum2))
                  {
                  seqWeights[seqnum2] = prevblock->portsets[pset].seqStream[seqnum2];
                  swsum += seqWeights[seqnum2];
                  ro_mult = (seqs[seqnum2]->T * seqs[seqnum2]->size) / prevblock->TD;
                  ro += ro_mult * seqWeights[seqnum2] * seqs[seqnum2]->portsets[pset].ES;
                  }
            }
         for (seqnum2 = 0; seqnum2 < SEQ_NUM_COUNT; seqnum2++)
            seqWeights[seqnum2] /= swsum;

         double Cin2 = 0;
         double CS2 = 0;
         if (ro > 1)
            ro = 1; // В парсинге последовательностей нужна обработка ветвящихся PDG
         for (seqnum2 = 0; seqnum2 < SEQ_NUM_COUNT; seqnum2++)
            {
            if (!(seqmask & (1 << seqnum2)))
               continue;
            Cin2 += (1 - ro) * seqWeights[seqnum2] * (seqs[seqnum2]->portsets[pset].usage * seqs[seqnum2]->CZ2 + 1 - seqs[seqnum2]->portsets[pset].usage);
            CS2 += seqWeights[seqnum2] * (seqs[seqnum2]->portsets[pset].CS2);
            }
         Cin2 += ro * CS2;
         if (Cin2 < 0) Cin2 = 0;

         double mult = (1.0 - (1 - Cin2) / (2 * block->seqcount)) * (Cin2 + CS2) / 2.0;
//            printf("  Seq %d pset %X ro %.3f Cin2 %.3f CS2 %.3f mult %.3f\n",seqnum,pmask,ro,Cin2,CS2,mult);

         double ql = 0;
         if (prevblock)
            {
            for (j = 0; j < PORTS_COUNT; j++)
               {
               if (!((1 << j) & pmask))
                  continue;
               ql += prevblock->qlength[j];
               }
            ql /= __builtin_popcount(pmask);
            }
         double W = agg->portsets[pset].ES * mult * ql;
         R[pset] = agg->portsets[pset].ES + W;
         T += agg->portsets[pset].usage * R[pset];
         }
      if (T * agg->size > block->TD)
         block->TD = T * agg->size;

      double portStreams[PORTS_COUNT] = {0};
      double qlen[PORTS_COUNT] = {0};

      for (i = 0; i < agg_psetscnt; i++)
         {
         pset = agg_psets[i];
         int pmask = get_portset_by_num(pset);
         int pcnt = __builtin_popcount(pmask);

//         block->portsets[pset].seqStream[seqnum] = agg->portsets[pset].prob / T;

         for (j = 0; j < PORTS_COUNT; j++)
            {
            if (!((1 << j) & pmask))
               continue;
            portStreams[j] += agg->portsets[pset].usage / pcnt;
            qlen[j] += agg->portsets[pset].usage / pcnt * R[pset] / T;
            }
         }

      for (j = 0; j < PORTS_COUNT; j++)
         {
//            printf("  Seq %d port %d qlen %.3f stream %.3f\n",seqnum,j,qlen[j],portStreams[j]);
         block->qlength[j] += qlen[j];
         }

      for (pset = 0; pset < PORT_SETS_COUNT; pset++)
         {
         int pmask = get_portset_by_num(pset);
         block->portsets[pset].seqStream[seqnum] = 0;

         for (j = 0; j < PORTS_COUNT; j++)
            {
            if (!((1 << j) & pmask))
               continue;
            block->portsets[pset].seqStream[seqnum] += portStreams[j];
            }
         }
      }

   block->TD += (sreg_prob + vreg_prob) * 4 * seqs[mseq]->size;
//   printf("  Sregs: %.2f, Vregs: %.2f, sz %.2f\n",sreg_prob,vreg_prob,seqs[mseq]->size);

   return block;
   }

int compare_seqs(const void *a,const void *b)
   {
   FSeqAggregate *s1 = *(FSeqAggregate **)a;
   FSeqAggregate *s2 = *(FSeqAggregate **)b; 
   if (s1->T * s1->size > s2->T * s2->size)
      return -1;
   if (s1->T * s1->size < s2->T * s2->size)
      return 1;
   return 0;
   }

int compare_seq_blocks(const void *a,const void *b)
   {
   FSeqBlock *b1 = *(FSeqBlock **)a;
   FSeqBlock *b2 = *(FSeqBlock **)b;
   if (!b1)
      return !b2 ? 0: 1;
   if (!b2)
      return -1;

   if (b1->seqcount > b2->seqcount)
      return -1;
   if (b1->seqcount < b2->seqcount)
      return 1;

   if (b1->TD > b2->TD)
      return -1;
   if (b1->TD < b2->TD)
      return 1;
   return 0;
   }


int main(int argc,char *argv[])
   {
   int i,j;

   int layer_buf1[1024], layer_buf2[1024];
   int *cur_layer = layer_buf1, *prev_layer = layer_buf2;
   int cur_layer_size = 0, prev_layer_size = 0;

   parser_init();
   init_port_sets();


   char *predefnames[]= {"sampleA.s","sampleB.s","sampleC.s","sampleD.s","sampleE.s","sampleF.s"};
   char **fnames = predefnames;
   int scnt = 6;

   if (argc - 1 > SEQ_NUM_COUNT)
      return printf("Too many input files, maximum count is %d\n",SEQ_NUM_COUNT),0;
   if (argc > 1)
      {
      scnt = argc - 1;
      fnames = &argv[1];
      }

   FSeqAggregate *seqs[SEQ_NUM_COUNT];

   char *basedir = "../../../samples/";
//   char *basedir = "samples/";
   int blockscount = 0;
   char fnamebuf[512];
   for (i = 0; i < scnt; i++)
      {
      sprintf(fnamebuf,"%s%s",basedir,fnames[i]);
      FInstructionSet *is = parser_read_file(fnamebuf);
      if (!is)
         goto main_exit;
         
      seqs[i] = make_seq_aggregate(is);
      free(is);

      strncpy(seqs[i]->seqname,fnames[i],15);
      seqs[i]->seqname[15] = 0;
      }
   qsort(seqs,scnt,sizeof(FSeqAggregate *),compare_seqs);

   for (i = 0; i < scnt; i++)
      printf ("Sequence %s: size %.f, cycle T %f, lat T %f \n",seqs[i]->seqname,seqs[i]->size,seqs[i]->T,seqs[i]->EZ);

   for (i = 0; i < scnt; i++)
      {
      uint32_t seqmask = 1 << i;
      FSeqBlock *work = make_block(1 << i,seqs);
      known_blocks[seqmask] = work;

      printf("Found block %X: len %f\n",seqmask,work->TD);

      blockscount++;
      prev_layer[prev_layer_size++] = seqmask;
      }

   do
      {
      for (i = 0; i < prev_layer_size ; i++)
         {
         FSeqBlock *work = known_blocks[prev_layer[i]];
         if (work->saturated)
            continue;
         int has_better = 0;
         for (j = 32 - __builtin_clz(work->seqmask); j < scnt; j++)
            {
            uint32_t seqmask = work->seqmask | (1 << j);
            FSeqBlock *nwork = make_block(seqmask,seqs);
            known_blocks[seqmask] = nwork;
            printf("Found block %X: len %f\n",seqmask,nwork->TD);
            blockscount++;
            cur_layer[cur_layer_size++] = seqmask;
            }
         if (!has_better)
            work->saturated = 1;
         }
      int *lswp = cur_layer;
      cur_layer = prev_layer;
      prev_layer = lswp;
      prev_layer_size = cur_layer_size;
      cur_layer_size = 0;
      }
   while (prev_layer_size);

   qsort(known_blocks,SEQ_NUM_COUNT * SEQ_NUM_COUNT,sizeof(FSeqBlock *),compare_seq_blocks);

   uint32_t full_mask = (1 << scnt) - 1;
   uint32_t csmask = 0;
   double clen = 0;
   
   int beststack[SEQ_NUM_COUNT] = {0};
   int stack[SEQ_NUM_COUNT] = {0};
   int beststsize = 0;
   int stack_pos = 0;
   double best = 100000;

   while (1)
      {
      int cp = stack[stack_pos];
      while (cp >= blockscount || clen + known_blocks[cp]->TD > best || (csmask & known_blocks[cp]->seqmask))
         { // Проверен последний блок в верхнем элементе стека или текущий результат уже хуже имеющегося
         if (cp >= blockscount)
            {
            if (stack_pos == 0)
               goto main_search_finish;
            stack_pos--;
            cp = stack[stack_pos];
            clen -= known_blocks[cp]->TD;
            csmask -= known_blocks[cp]->seqmask;
            }
         stack[stack_pos] = ++cp;
         }
      clen += known_blocks[cp]->TD;
      csmask |= known_blocks[cp]->seqmask;

      if (csmask == full_mask)
         { // Полное покрытие
         if (clen < best)
            { // Лучший вариант
            best = clen;
            memcpy(beststack,stack,sizeof(stack));
            beststsize = stack_pos + 1;
            }
         clen -= known_blocks[cp]->TD;
         csmask -= known_blocks[cp]->seqmask;
         stack[stack_pos] = ++cp;
         }
      else
         {
         stack_pos++;
         stack[stack_pos] = cp + 1;
         }
      }

main_search_finish:
   if (beststsize)
      {
      printf("Best: %f\n",best);

      for(i = 0; i < beststsize; i++)
         {
         if (i)
            printf(" + ");
         int ast = 0;
         for (j = 0; j < scnt; j++)
            {
            if ((1 << j) & known_blocks[beststack[i]]->seqmask)
               {
               if (ast)
                  printf(" * ");
               ast = 1;
               printf("%s",seqs[j]->seqname);
               }
            }
         }
      printf("\n");
      }
main_exit:
   return 0;
   }