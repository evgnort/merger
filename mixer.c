#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "codeseq.h"

FSeqBlock *known_blocks[1 << SEQ_NUM_COUNT];

FSeqBlock * make_block(uint32_t seqmask,FSeqAggregate **seqs)
   {
   FSeqBlock *block = (FSeqBlock *)calloc(1,sizeof(FSeqBlock));
   int pset,pset2,seqnum,seqnum2,i;

   block->seqmask = seqmask;
   block->seqcount = __builtin_popcount(seqmask);

   block->TD = 0;

   for (seqnum = 0; seqnum < SEQ_NUM_COUNT; seqnum++)
      {
      if (!(seqmask & (1 << seqnum)))
         continue;

      FSeqAggregate *agg = seqs[seqnum];
      FSeqBlock *prevblock = known_blocks[seqmask - (1 << seqnum)];

      double T = agg->EZ;
      double R[PORT_SETS_COUNT] = {0};
      for (pset = 0; pset < PORT_SETS_COUNT; pset++)
         {
         if (!agg->portsets[pset].prob)
            continue;
         int pmask = get_portset_by_num(pset);

         double seqWeights[SEQ_NUM_COUNT] = {0};

         seqWeights[seqnum] = agg->portsets[pset].prob / agg->T;

         double swsum = seqWeights[seqnum];
         double ro = seqWeights[seqnum] * agg->portsets[pset].ES;
         if (prevblock)
            {
            for (seqnum2 = 0; seqnum2 < SEQ_NUM_COUNT; seqnum2++)
               if (prevblock->seqmask & (1 << seqnum2))
                  {
                  seqWeights[seqnum2] = prevblock->portsets[pset].seqL[seqnum2];
                  swsum += seqWeights[seqnum2];
                  ro += seqWeights[seqnum2] * agg->portsets[pset].ES;
                  }
            }
         for (seqnum2 = 0; seqnum2 < SEQ_NUM_COUNT; seqnum2++)
            seqWeights[seqnum2] /= swsum;

         double Cin2 = 0;
         double CS2 = 0;
         for (seqnum2 = 0; seqnum2 < SEQ_NUM_COUNT; seqnum2++)
            {
            if (!(seqmask & (1 << seqnum2)))
               continue;
            Cin2 += (1 - ro) * seqWeights[seqnum2] * (seqs[seqnum2]->portsets[pset].prob * seqs[seqnum2]->CZ2 + 1 - seqs[seqnum2]->portsets[pset].prob);
            CS2 += seqWeights[seqnum2] * (seqs[seqnum2]->portsets[pset].CS2);
            }
         Cin2 += ro * CS2;

         double mult = (1.0 - (1 - Cin2) / (2 * block->seqcount)) * (Cin2 + CS2) / 2.0;

         double ql = 0;
         if (prevblock)
            {
            for (i = 0; i < PORTS_COUNT; i++)
               {
               if (!((1 << i) & pmask))
                  continue;
               ql += prevblock->qlength[i];
               }
            ql /= __builtin_popcount(pmask);
            }
         double W = agg->portsets[pset].ES * mult * ql;
         R[pset] = agg->portsets[pset].ES + W;
         T += agg->portsets[pset].prob * R[pset];
         }
      if (T * agg->size > block->TD)
         block->TD = T * agg->size;
//      double portL[PORTS_COUNT] = {0};

      for (pset = 0; pset < PORT_SETS_COUNT; pset++)
         {
         int pmask = get_portset_by_num(pset);
         int pcnt = __builtin_popcount(pmask);

         if (!agg->portsets[pset].prob)
            continue;

         block->portsets[pset].seqL[seqnum] = agg->portsets[pset].prob / T;

         for (i = 0; i < PORTS_COUNT; i++)
            {
            if (!((1 << i) & pmask))
               continue;
//            portL[i] += agg->portsets[pset].prob / pcnt;
            block->qlength[i] += agg->portsets[pset].prob / pcnt * R[pset] / T;
            }
         }
      }

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
   int i,j, scnt;

   int layer_buf1[1024], layer_buf2[1024];
   int *cur_layer = layer_buf1, *prev_layer = layer_buf2;
   int cur_layer_size = 0, prev_layer_size = 0;

   parser_init();
   init_port_sets();

   if (argc <= 1)
      return puts("No input files"),0;
   scnt = argc - 1;
   if (argc - 1 > SEQ_NUM_COUNT)
      return printf("Too many input files, maximum count is %d\n",SEQ_NUM_COUNT),0;

   FSeqAggregate *seqs[SEQ_NUM_COUNT];
   FSeqBlock *initial_blocks[SEQ_NUM_COUNT];

   int blockscount = 0;
   for (i = 0; i < scnt; i++)
      {

      FInstructionSet *is = parser_read_file(argv[i+1]);
      seqs[i] = make_seq_aggregate(is);
      free(is);
      strncpy(seqs[i]->seqname,argv[i+1],16);
      seqs[i]->seqname[15] = 0;
      }
   qsort(seqs,scnt,sizeof(FSeqAggregate *),compare_seqs);

   for (i = 0; i < scnt; i++)
      {
      uint32_t seqmask = 1 << i;
      FSeqBlock *work = make_block(1 << i,seqs);
      known_blocks[seqmask] = work;
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

   double best = 100000;
   qsort(known_blocks,SEQ_NUM_COUNT * SEQ_NUM_COUNT,sizeof(FSeqBlock *),compare_seq_blocks);

   uint32_t full_mask = (1 << scnt) - 1;
   uint32_t csmask = known_blocks[0]->seqmask;
   uint32_t clen = known_blocks[0]->TD;
   
   int beststack[SEQ_NUM_COUNT] = {0};
   int stack[SEQ_NUM_COUNT] = {0};
   int beststsize = 0;
   int stack_pos = 1;
   while (1)
      {
      int np = stack[stack_pos];
      if (np >= blockscount)
         {
step_backward:
         if (stack_pos == 0)
            break;
         stack_pos--;
         clen -= known_blocks[stack[stack_pos]]->TD;
         csmask -= known_blocks[stack[stack_pos]]->seqmask;
         stack[stack_pos]++;
         continue;
         }
      double nlen = clen + known_blocks[np]->TD;
      if (!(known_blocks[np]->seqmask & csmask) && nlen < best)
         {
         uint32_t nmask = known_blocks[np]->seqmask | csmask;
         if (nmask == full_mask)
            { // Полное покрытие
            best = clen + known_blocks[np]->TD;
            memcpy(beststack,stack,sizeof(stack));
            beststsize = stack_pos + 1;
            goto step_backward;
            }
         // Добавляем новый блок к стеку
         stack[++stack_pos] = np;
         csmask = nmask;
         clen = nlen;
         }
      stack[stack_pos]++;
      }
main_finish:

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
   return 0;
   }