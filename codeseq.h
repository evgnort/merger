#ifndef _CODE_SEQ_H
#define _CODE_SEQ_H

#include "defines.h"
#include "parser.h"

typedef struct FTickPortUsageTg {
   double probs[MAX_PORT_PRESSURE]; 
   } FTickPortUsage;

typedef struct FTickRegUsageTg {
   int reg_rd[REGS_COUNT];
   double reg_rp_sorted[REGS_COUNT];
   int reg_cnt;
   } FTickRegUsage;

#define SCALAR_REGS 0
#define VECTOR_REGS 1

#define REG_SETS_COUNT 2

// ќписание такта дл€ поиска перебором
typedef struct FTickTg {
   FTickPortUsage ports[PORTS_COUNT];
   FTickRegUsage regs[REG_SETS_COUNT];
   int sline; // source code line numbers
   } FTick;

typedef struct FTickSetTg {
   int ticks_count;
   FTick ticks[];
   } FTickSet;

FTickSet *make_tick_seq(FInstructionSet *is);

// ќписание временных р€дов дл€ поиска через FFT
typedef struct FTimelineTg {
   int size;
   double *ports_usage[PORTS_COUNT][MAX_PORT_PRESSURE];
   double *regs_usage[REG_SETS_COUNT][REGS_COUNT];
   } FTimeline;

FTimeline *make_timeline(FTickSet *ts);
void free_timeline(FTimeline *tl);

#define SEQ_NUM_COUNT 10

// »сходные данные набора приборов в одной последовательности
typedef struct FDeviceSetDataTg {
   int use_count;
   double usage;
   double ES;
   double CS2;
   } FDeviceSetData;

// ’арактеристики набора приборов в блоке последовательностей
typedef struct FPortSetTg {
   double seqStream[SEQ_NUM_COUNT];
   } FPortSet;

#define PORT_SETS_COUNT 16

typedef struct FSeqAggregateTg {
   char seqname[16];
   FDeviceSetData portsets[PORT_SETS_COUNT];
   double size;
   double T;
   double EZ;
   double CZ2;
   } FSeqAggregate;

void init_port_sets(void);
int get_portset_by_num(int psnum);
const char *get_psname_by_num(int psnum);

FSeqAggregate *make_seq_aggregate(FInstructionSet *is);

typedef struct FSeqBlockTg {
   uint32_t seqmask;
   int seqcount;
   FPortSet portsets[PORT_SETS_COUNT];
   double qlength[PORTS_COUNT];
   int saturated;
   double TD;
   } FSeqBlock;


#endif