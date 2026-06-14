#ifndef _PARSER_H
#define _PARSER_H

#include "defines.h"

enum ERegistersTg {
   REG_NONE = -1,

   REG_RAX,
   REG_RBX,
   REG_RCX,
   REG_RDX, 
   REG_RSI,
   REG_RDI,
   REG_RBP,
   REG_RSP,
   REG_R8,
   REG_R9,
   REG_R10,
   REG_R11,
   REG_R12,
   REG_R13,
   REG_R14,
   REG_R15,

   REG_YMM0,
   REG_YMM1,
   REG_YMM2,
   REG_YMM3,
   REG_YMM4,
   REG_YMM5,
   REG_YMM6,
   REG_YMM7,
   REG_YMM8,
   REG_YMM9,
   REG_YMM10,
   REG_YMM11,
   REG_YMM12,
   REG_YMM13,
   REG_YMM14,
   REG_YMM15,

   REG_MAX
};

#define PORT_0 1
#define PORT_1 2
#define PORT_2 4
#define PORT_3 8
#define PORT_4 16
#define PORT_5 32
#define PORT_6 64
#define PORT_7 128

#define PORT_01 (PORT_0 | PORT_1)
#define PORT_23 (PORT_2 | PORT_3)
#define PORT_237 (PORT_2 | PORT_3 | PORT_7)
#define PORT_015 (PORT_0 | PORT_1 | PORT_5)
#define PORT_15 (PORT_1 | PORT_5)
#define PORT_06 (PORT_0 | PORT_6)
#define PORT_0156 (PORT_0 | PORT_1 | PORT_5 | PORT_6)

#define MAX_PORT_PRESSURE 4
#define AVG_WINDOW 4

#define PORTS_COUNT 8
#define REGS_COUNT 16



#define MOP_UNCHAINED 1

typedef struct FMicroOpTg {
   uint32_t portmask;
   uint32_t latency;
   uint32_t duration;
   uint32_t flags;
   } FMicroOp;

typedef struct FInstructionDefTg {
   char mnem[16];
   uint8_t operands[4];
} FInstructionDef;

#define IF_TARGET_DEP 0x01
#define IF_NO_TARGET 0x02

typedef struct FInstructionDescTg {
   FInstructionDef def;
   int mops_cnt;
   FMicroOp ops[8];
   int flags;
   int latency;
} FInstructionDesc;

#define OP_NON 0
#define OP_REG 1
#define OP_XMM 2
#define OP_YMM 3

// Простая память, Base, Base + Index, Base + Disp
#define OP_MEM 4

// Сложная память
#define OP_MEC 5

#define OP_VAL 6
#define OP_BAD 7

typedef struct FInstructionTg {
   FInstructionDef def;
   int mops_cnt;
   FMicroOp *ops;
   int targ_dep;
   int latency;
   int tick;
   int treg;
   int line;
   int reg_next_usage[REG_MAX];
} FInstruction;

typedef struct FInstructionSetTg {
   int inst_cnt;
   int reg_initial_usage[REG_MAX];
   FInstruction instructions[];
   } FInstructionSet;

extern int MAX_LATENCY;

void parser_init(void);

FInstructionSet *parser_read_file(const char *filename);

#endif