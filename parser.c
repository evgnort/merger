#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "parser.h"

FInstructionDesc instruction_set[] = {
   {{"movabsq", {OP_REG, OP_NON, OP_NON, OP_REG}}, 1, {{PORT_0156,1,1,0}},0},
   {{"movq", {OP_REG, OP_NON, OP_NON, OP_REG}}, 1, {{PORT_0156,1,1,0}},0},
   {{"movl", {OP_REG, OP_NON, OP_NON, OP_REG}}, 1, {{PORT_0156,1,1,0}},0},
   {{"movw", {OP_REG, OP_NON, OP_NON, OP_REG}}, 1, {{PORT_0156,1,1,0}},0},
   {{"movb", {OP_REG, OP_NON, OP_NON, OP_REG}}, 1, {{PORT_0156,1,1,0}},0},
   {{"movq", {OP_VAL, OP_NON, OP_NON, OP_REG}}, 1, {{PORT_0156,1,1,0}},0},
   {{"movl", {OP_VAL, OP_NON, OP_NON, OP_REG}}, 1, {{PORT_0156,1,1,0}},0},
   {{"movw", {OP_VAL, OP_NON, OP_NON, OP_REG}}, 1, {{PORT_0156,1,1,0}},0},
   {{"movb", {OP_VAL, OP_NON, OP_NON, OP_REG}}, 1, {{PORT_0156,1,1,0}},0},
   {{"movq", {OP_REG, OP_NON, OP_NON, OP_MEM}}, 2, {{PORT_237,1,1,MOP_UNCHAINED},{PORT_4,2,1,0}},0},
   {{"movl", {OP_REG, OP_NON, OP_NON, OP_MEM}}, 2, {{PORT_237,1,1,MOP_UNCHAINED},{PORT_4,2,1,0}},0},
   {{"movw", {OP_REG, OP_NON, OP_NON, OP_MEM}}, 2, {{PORT_237,1,1,MOP_UNCHAINED},{PORT_4,2,1,0}},0},
   {{"movb", {OP_REG, OP_NON, OP_NON, OP_MEM}}, 2, {{PORT_237,1,1,MOP_UNCHAINED},{PORT_4,2,1,0}},0},
   {{"movq", {OP_VAL, OP_NON, OP_NON, OP_MEM}}, 2, {{PORT_237,1,1,MOP_UNCHAINED},{PORT_4,2,1,0}},0},
   {{"movl", {OP_VAL, OP_NON, OP_NON, OP_MEM}}, 2, {{PORT_237,1,1,MOP_UNCHAINED},{PORT_4,2,1,0}},0},
   {{"movw", {OP_VAL, OP_NON, OP_NON, OP_MEM}}, 2, {{PORT_237,1,1,MOP_UNCHAINED},{PORT_4,2,1,0}},0},
   {{"movb", {OP_VAL, OP_NON, OP_NON, OP_MEM}}, 2, {{PORT_237,1,1,MOP_UNCHAINED},{PORT_4,2,1,0}},0},
   {{"movq", {OP_REG, OP_NON, OP_NON, OP_MEC}}, 2, {{PORT_23,1,1,MOP_UNCHAINED},{PORT_4,2,1,0}},0},
   {{"movl", {OP_REG, OP_NON, OP_NON, OP_MEC}}, 2, {{PORT_23,1,1,MOP_UNCHAINED},{PORT_4,2,1,0}},0},
   {{"movw", {OP_REG, OP_NON, OP_NON, OP_MEC}}, 2, {{PORT_23,1,1,MOP_UNCHAINED},{PORT_4,2,1,0}},0},
   {{"movb", {OP_REG, OP_NON, OP_NON, OP_MEC}}, 2, {{PORT_23,1,1,MOP_UNCHAINED},{PORT_4,2,1,0}},0},
   {{"movq", {OP_VAL, OP_NON, OP_NON, OP_MEC}}, 2, {{PORT_23,1,1,MOP_UNCHAINED},{PORT_4,2,1,0}},0},
   {{"movl", {OP_VAL, OP_NON, OP_NON, OP_MEC}}, 2, {{PORT_23,1,1,MOP_UNCHAINED},{PORT_4,2,1,0}},0},
   {{"movw", {OP_VAL, OP_NON, OP_NON, OP_MEC}}, 2, {{PORT_23,1,1,MOP_UNCHAINED},{PORT_4,2,1,0}},0},
   {{"movb", {OP_VAL, OP_NON, OP_NON, OP_MEC}}, 2, {{PORT_23,1,1,MOP_UNCHAINED},{PORT_4,2,1,0}},0},
   {{"movq", {OP_MEM, OP_NON, OP_NON, OP_REG}}, 1, {{PORT_23,4,1,0}},0},
   {{"movl", {OP_MEM, OP_NON, OP_NON, OP_REG}}, 1, {{PORT_23,4,1,0}},0},
   {{"movw", {OP_MEM, OP_NON, OP_NON, OP_REG}}, 1, {{PORT_23,5,1,0}},0},
   {{"movb", {OP_MEM, OP_NON, OP_NON, OP_REG}}, 1, {{PORT_23,5,1,0}},0},
   {{"movq", {OP_MEC, OP_NON, OP_NON, OP_REG}}, 1, {{PORT_23,5,1,0}},0},
   {{"movl", {OP_MEC, OP_NON, OP_NON, OP_REG}}, 1, {{PORT_23,5,1,0}},0},
   {{"movw", {OP_MEC, OP_NON, OP_NON, OP_REG}}, 1, {{PORT_23,6,1,0}},0},
   {{"movb", {OP_MEC, OP_NON, OP_NON, OP_REG}}, 1, {{PORT_23,6,1,0}},0},
   {{"movzwl", {OP_REG, OP_NON, OP_NON, OP_REG}}, 1, {{PORT_0|PORT_1|PORT_5|PORT_6,1,1,0}},0},
   {{"movzbl", {OP_REG, OP_NON, OP_NON, OP_REG}}, 1, {{PORT_0|PORT_1|PORT_5|PORT_6,1,1,0}},0},
   {{"movzwq", {OP_REG, OP_NON, OP_NON, OP_REG}}, 1, {{PORT_0|PORT_1|PORT_5|PORT_6,1,1,0}},0},
   {{"movzbq", {OP_REG, OP_NON, OP_NON, OP_REG}}, 1, {{PORT_0|PORT_1|PORT_5|PORT_6,1,1,0}},0},
   {{"movzbw", {OP_REG, OP_NON, OP_NON, OP_REG}}, 1, {{PORT_0|PORT_1|PORT_5|PORT_6,1,1,0}},0},

   {{"movswl", {OP_REG, OP_NON, OP_NON, OP_REG}}, 1, {{PORT_0156,1,1,0}},0},
   {{"movsbl", {OP_REG, OP_NON, OP_NON, OP_REG}}, 1, {{PORT_0156,1,1,0}},0},
   {{"movswq", {OP_REG, OP_NON, OP_NON, OP_REG}}, 1, {{PORT_0156,1,1,0}},0},
   {{"movsbq", {OP_REG, OP_NON, OP_NON, OP_REG}}, 1, {{PORT_0156,1,1,0}},0},
   {{"movsbw", {OP_REG, OP_NON, OP_NON, OP_REG}}, 1, {{PORT_0156,1,1,0}},0},
   {{"movzwl", {OP_MEM, OP_NON, OP_NON, OP_REG}}, 1, {{PORT_23,4,1,0}},0},
   {{"movzbl", {OP_MEM, OP_NON, OP_NON, OP_REG}}, 1, {{PORT_23,4,1,0}},0},
   {{"movzwq", {OP_MEM, OP_NON, OP_NON, OP_REG}}, 1, {{PORT_23,4,1,0}},0},
   {{"movzbq", {OP_MEM, OP_NON, OP_NON, OP_REG}}, 1, {{PORT_23,4,1,0}},0},
   {{"movzbw", {OP_MEM, OP_NON, OP_NON, OP_REG}}, 1, {{PORT_23,5,1,0}},0},

   {{"movswl", {OP_MEM, OP_NON, OP_NON, OP_REG}}, 1, {{PORT_23,5,1,0}},0},
   {{"movsbl", {OP_MEM, OP_NON, OP_NON, OP_REG}}, 1, {{PORT_23,5,1,0}},0},
   {{"movswq", {OP_MEM, OP_NON, OP_NON, OP_REG}}, 1, {{PORT_23,5,1,0}},0},
   {{"movsbq", {OP_MEM, OP_NON, OP_NON, OP_REG}}, 1, {{PORT_23,5,1,0}},0},
   {{"movsbw", {OP_MEM, OP_NON, OP_NON, OP_REG}}, 1, {{PORT_23,6,1,0}},0},
   {{"movzwl", {OP_MEC, OP_NON, OP_NON, OP_REG}}, 1, {{PORT_23,5,1,0}},0},
   {{"movzbl", {OP_MEC, OP_NON, OP_NON, OP_REG}}, 1, {{PORT_23,5,1,0}},0},
   {{"movzwq", {OP_MEC, OP_NON, OP_NON, OP_REG}}, 1, {{PORT_23,5,1,0}},0},
   {{"movzbq", {OP_MEC, OP_NON, OP_NON, OP_REG}}, 1, {{PORT_23,5,1,0}},0},
   {{"movzbw", {OP_MEC, OP_NON, OP_NON, OP_REG}}, 1, {{PORT_23,6,1,0}},0},

   {{"movswl", {OP_MEC, OP_NON, OP_NON, OP_REG}}, 1, {{PORT_23,6,1,0}},0},
   {{"movsbl", {OP_MEC, OP_NON, OP_NON, OP_REG}}, 1, {{PORT_23,6,1,0}},0},
   {{"movswq", {OP_MEC, OP_NON, OP_NON, OP_REG}}, 1, {{PORT_23,6,1,0}},0},
   {{"movsbq", {OP_MEC, OP_NON, OP_NON, OP_REG}}, 1, {{PORT_23,6,1,0}},0},
   {{"movsbw", {OP_MEC, OP_NON, OP_NON, OP_REG}}, 1, {{PORT_23,7,1,0}},0},
   {{"leal", {OP_MEM, OP_NON, OP_NON, OP_REG}}, 1, {{PORT_15,1,1,0}},0},
   {{"leaq", {OP_MEM, OP_NON, OP_NON, OP_REG}}, 1, {{PORT_15,1,1,0}},0},

   {{"leal", {OP_MEC, OP_NON, OP_NON, OP_REG}}, 1, {{PORT_1,3,1,0}},0},
   {{"leaq", {OP_MEC, OP_NON, OP_NON, OP_REG}}, 1, {{PORT_1,3,1,0}},0},
   {{"addb", {OP_REG, OP_NON, OP_NON, OP_REG}}, 1, {{PORT_0156,1,1,0}},0},
   {{"addb", {OP_MEM, OP_NON, OP_NON, OP_REG}}, 2, {{PORT_23,4,1,0},{PORT_0156,1,1,0}},0},
   {{"addb", {OP_MEC, OP_NON, OP_NON, OP_REG}}, 2, {{PORT_23,5,1,0},{PORT_0156,1,1,0}},0},
   {{"addb", {OP_REG, OP_NON, OP_NON, OP_MEM}}, 4, {{PORT_23,4,1,0},{PORT_0156,1,1,0},{PORT_237,1,1,MOP_UNCHAINED},{PORT_4,2,1,0}},0},
   {{"addb", {OP_REG, OP_NON, OP_NON, OP_MEC}}, 4, {{PORT_23,5,1,0},{PORT_0156,1,1,0},{PORT_23,1,1,MOP_UNCHAINED},{PORT_4,2,1,0}},0},

   {{"addw", {OP_REG, OP_NON, OP_NON, OP_REG}}, 1, {{PORT_0156,1,1,0}},0},
   {{"addw", {OP_MEM, OP_NON, OP_NON, OP_REG}}, 2, {{PORT_23,4,1,0},{PORT_0156,1,1,0}},0},
   {{"addw", {OP_MEC, OP_NON, OP_NON, OP_REG}}, 2, {{PORT_23,5,1,0},{PORT_0156,1,1,0}},0},
   {{"addw", {OP_REG, OP_NON, OP_NON, OP_MEM}}, 4, {{PORT_23,4,1,0},{PORT_0156,1,1,0},{PORT_237,1,1,MOP_UNCHAINED},{PORT_4,2,1,0}},0},
   {{"addw", {OP_REG, OP_NON, OP_NON, OP_MEC}}, 4, {{PORT_23,5,1,0},{PORT_0156,1,1,0},{PORT_23,1,1,MOP_UNCHAINED},{PORT_4,2,1,0}},0},

   {{"addl", {OP_REG, OP_NON, OP_NON, OP_REG}}, 1, {{PORT_0156,1,1,0}},0},
   {{"addl", {OP_MEM, OP_NON, OP_NON, OP_REG}}, 2, {{PORT_23,4,1,0},{PORT_0156,1,1,0}},0},
   {{"addl", {OP_MEC, OP_NON, OP_NON, OP_REG}}, 2, {{PORT_23,5,1,0},{PORT_0156,1,1,0}},0},
   {{"addl", {OP_REG, OP_NON, OP_NON, OP_MEM}}, 4, {{PORT_23,4,1,0},{PORT_0156,1,1,0},{PORT_237,1,1,MOP_UNCHAINED},{PORT_4,2,1,0}},0},
   {{"addl", {OP_REG, OP_NON, OP_NON, OP_MEC}}, 4, {{PORT_23,5,1,0},{PORT_0156,1,1,0},{PORT_23,1,1,MOP_UNCHAINED},{PORT_4,2,1,0}},0},

   {{"addq", {OP_VAL, OP_NON, OP_NON, OP_REG}}, 1, {{PORT_0156,1,1,0}},0},
   {{"addq", {OP_REG, OP_NON, OP_NON, OP_REG}}, 1, {{PORT_0156,1,1,0}},0},
   {{"addq", {OP_MEM, OP_NON, OP_NON, OP_REG}}, 2, {{PORT_23,4,1,0},{PORT_0156,1,1,0}},0},
   {{"addq", {OP_MEC, OP_NON, OP_NON, OP_REG}}, 2, {{PORT_23,5,1,0},{PORT_0156,1,1,0}},0},
   {{"addq", {OP_REG, OP_NON, OP_NON, OP_MEM}}, 4, {{PORT_23,4,1,0},{PORT_0156,1,1,0},{PORT_237,1,1,MOP_UNCHAINED},{PORT_4,2,1,0}},0},
   {{"addq", {OP_REG, OP_NON, OP_NON, OP_MEC}}, 4, {{PORT_23,5,1,0},{PORT_0156,1,1,0},{PORT_23,1,1,MOP_UNCHAINED},{PORT_4,2,1,0}},0},


   {{"subb", {OP_REG, OP_NON, OP_NON, OP_REG}}, 1, {{PORT_0156,1,1,0}},0},
   {{"subb", {OP_MEM, OP_NON, OP_NON, OP_REG}}, 2, {{PORT_23,4,1,0},{PORT_0156,1,1,0}},0},
   {{"subb", {OP_MEC, OP_NON, OP_NON, OP_REG}}, 2, {{PORT_23,5,1,0},{PORT_0156,1,1,0}},0},
   {{"subb", {OP_REG, OP_NON, OP_NON, OP_MEM}}, 4, {{PORT_23,4,1,0},{PORT_0156,1,1,0},{PORT_237,1,1,MOP_UNCHAINED},{PORT_4,2,1,0}},0},
   {{"subb", {OP_REG, OP_NON, OP_NON, OP_MEC}}, 4, {{PORT_23,5,1,0},{PORT_0156,1,1,0},{PORT_23,1,1,MOP_UNCHAINED},{PORT_4,2,1,0}},0},

   {{"subw", {OP_REG, OP_NON, OP_NON, OP_REG}}, 1, {{PORT_0156,1,1,0}},0},
   {{"subw", {OP_MEM, OP_NON, OP_NON, OP_REG}}, 2, {{PORT_23,4,1,0},{PORT_0156,1,1,0}},0},
   {{"subw", {OP_MEC, OP_NON, OP_NON, OP_REG}}, 2, {{PORT_23,5,1,0},{PORT_0156,1,1,0}},0},
   {{"subw", {OP_REG, OP_NON, OP_NON, OP_MEM}}, 4, {{PORT_23,4,1,0},{PORT_0156,1,1,0},{PORT_237,1,1,MOP_UNCHAINED},{PORT_4,2,1,0}},0},
   {{"subw", {OP_REG, OP_NON, OP_NON, OP_MEC}}, 4, {{PORT_23,5,1,0},{PORT_0156,1,1,0},{PORT_23,1,1,MOP_UNCHAINED},{PORT_4,2,1,0}},0},

   {{"subl", {OP_REG, OP_NON, OP_NON, OP_REG}}, 1, {{PORT_0156,1,1,0}},0},
   {{"subl", {OP_MEM, OP_NON, OP_NON, OP_REG}}, 2, {{PORT_23,4,1,0},{PORT_0156,1,1,0}},0},
   {{"subl", {OP_MEC, OP_NON, OP_NON, OP_REG}}, 2, {{PORT_23,5,1,0},{PORT_0156,1,1,0}},0},
   {{"subl", {OP_REG, OP_NON, OP_NON, OP_MEM}}, 4, {{PORT_23,4,1,0},{PORT_0156,1,1,0},{PORT_237,1,1,MOP_UNCHAINED},{PORT_4,2,1,0}},0},
   {{"subl", {OP_REG, OP_NON, OP_NON, OP_MEC}}, 4, {{PORT_23,5,1,0},{PORT_0156,1,1,0},{PORT_23,1,1,MOP_UNCHAINED},{PORT_4,2,1,0}},0},

   {{"subq", {OP_REG, OP_NON, OP_NON, OP_REG}}, 1, {{PORT_0156,1,1,0}},0},
   {{"subq", {OP_MEM, OP_NON, OP_NON, OP_REG}}, 2, {{PORT_23,4,1,0},{PORT_0156,1,1,0}},0},
   {{"subq", {OP_MEC, OP_NON, OP_NON, OP_REG}}, 2, {{PORT_23,5,1,0},{PORT_0156,1,1,0}},0},
   {{"subq", {OP_REG, OP_NON, OP_NON, OP_MEM}}, 4, {{PORT_23,4,1,0},{PORT_0156,1,1,0},{PORT_237,1,1,MOP_UNCHAINED},{PORT_4,2,1,0}},0},
   {{"subq", {OP_REG, OP_NON, OP_NON, OP_MEC}}, 4, {{PORT_23,5,1,0},{PORT_0156,1,1,0},{PORT_23,1,1,MOP_UNCHAINED},{PORT_4,2,1,0}},0},
   {{"vmovq", {OP_XMM, OP_NON, OP_NON, OP_XMM}}, 1, {{PORT_015,1,1,0}},0},

   {{"vmovd", {OP_REG, OP_NON, OP_NON, OP_XMM}}, 1, {{PORT_5,3,1,0}},0},
   {{"vmovq", {OP_REG, OP_NON, OP_NON, OP_XMM}}, 1, {{PORT_5,3,1,0}},0},

   {{"vmovd", {OP_MEM, OP_NON, OP_NON, OP_XMM}}, 1, {{PORT_23,4,1,0}},0},
   {{"vmovq", {OP_MEM, OP_NON, OP_NON, OP_XMM}}, 1, {{PORT_23,4,1,0}},0},

   {{"vmovd", {OP_MEC, OP_NON, OP_NON, OP_XMM}}, 1, {{PORT_23,4,1,0}},0},
   {{"vmovq", {OP_MEC, OP_NON, OP_NON, OP_XMM}}, 1, {{PORT_23,4,1,0}},0},

   {{"vmovd", {OP_XMM, OP_NON, OP_NON, OP_REG}}, 1, {{PORT_0,3,1,0}},0},
   {{"vmovq", {OP_XMM, OP_NON, OP_NON, OP_REG}}, 1, {{PORT_0,3,1,0}},0},

   {{"vmovd", {OP_XMM, OP_NON, OP_NON, OP_MEM}}, 2, {{PORT_237,1,1,MOP_UNCHAINED},{PORT_4,2,1,0}},0},
   {{"vmovq", {OP_XMM, OP_NON, OP_NON, OP_MEM}}, 2, {{PORT_237,1,1,MOP_UNCHAINED},{PORT_4,2,1,0}},0},

   {{"vmovd", {OP_XMM, OP_NON, OP_NON, OP_MEC}}, 2, {{PORT_23,1,1,MOP_UNCHAINED},{PORT_4,2,1,0}},0},
   {{"vmovq", {OP_XMM, OP_NON, OP_NON, OP_MEC}}, 2, {{PORT_23,1,1,MOP_UNCHAINED},{PORT_4,2,1,0}},0},

/* ==================== VMOVDQU (Невыровненный доступ) ==================== */
/* 128-битные версии (XMM) */
   {{"vmovdqu", {OP_XMM, OP_NON, OP_NON, OP_XMM}}, 0, {}},
   {{"vmovdqu", {OP_MEM, OP_NON, OP_NON, OP_XMM}}, 1, {{PORT_23,6,1,0}},0},
   {{"vmovdqu", {OP_MEC, OP_NON, OP_NON, OP_XMM}}, 1, {{PORT_23,6,1,0}},0},
   {{"vmovdqu", {OP_XMM, OP_NON, OP_NON, OP_MEM}}, 2, {{PORT_237,1,1,MOP_UNCHAINED},{PORT_4,2,1,0}},0},
   {{"vmovdqu", {OP_XMM, OP_NON, OP_NON, OP_MEC}}, 2, {{PORT_23,1,1,MOP_UNCHAINED},{PORT_4,2,1,0}},0},
/* 256-битные версии (YMM) */
   {{"vmovdqu", {OP_YMM, OP_NON, OP_NON, OP_YMM}}, 0, {}},
   {{"vmovdqu", {OP_MEM, OP_NON, OP_NON, OP_YMM}}, 1, {{PORT_23,7,1,0}},0},
   {{"vmovdqu", {OP_MEC, OP_NON, OP_NON, OP_YMM}}, 1, {{PORT_23,7,1,0}},0},
   {{"vmovdqu", {OP_YMM, OP_NON, OP_NON, OP_MEM}}, 2, {{PORT_237,1,1,MOP_UNCHAINED},{PORT_4,2,1,0}},0},
   {{"vmovdqu", {OP_YMM, OP_NON, OP_NON, OP_MEC}}, 2, {{PORT_23,1,1,MOP_UNCHAINED},{PORT_4,2,1,0}},0},

/* ==================== VMOVUPS (Невыровненный доступ) ==================== */
/* 128-битные версии (XMM) */
   {{"vmovups", {OP_XMM, OP_NON, OP_NON, OP_XMM}}, 0, {}},
   {{"vmovups", {OP_MEM, OP_NON, OP_NON, OP_XMM}}, 1, {{PORT_23,6,1,0}},0},
   {{"vmovups", {OP_MEC, OP_NON, OP_NON, OP_XMM}}, 1, {{PORT_23,6,1,0}},0},
   {{"vmovups", {OP_XMM, OP_NON, OP_NON, OP_MEM}}, 2, {{PORT_237,1,1,MOP_UNCHAINED},{PORT_4,2,1,0}},0},
   {{"vmovups", {OP_XMM, OP_NON, OP_NON, OP_MEC}}, 2, {{PORT_23,1,1,MOP_UNCHAINED},{PORT_4,2,1,0}},0},
/* 256-битные версии (YMM) */
   {{"vmovups", {OP_YMM, OP_NON, OP_NON, OP_YMM}}, 0, {}},
   {{"vmovups", {OP_MEM, OP_NON, OP_NON, OP_YMM}}, 1, {{PORT_23,7,1,0}},0},
   {{"vmovups", {OP_MEC, OP_NON, OP_NON, OP_YMM}}, 1, {{PORT_23,7,1,0}},0},
   {{"vmovups", {OP_YMM, OP_NON, OP_NON, OP_MEM}}, 2, {{PORT_237,1,1,MOP_UNCHAINED},{PORT_4,2,1,0}},0},
   {{"vmovups", {OP_YMM, OP_NON, OP_NON, OP_MEC}}, 2, {{PORT_23,1,1,MOP_UNCHAINED},{PORT_4,2,1,0}},0},

/* ==================== VMOVLPS ==================== */

   {{"vmovlps", {OP_XMM, OP_NON, OP_NON, OP_MEM}}, 2, {{PORT_237,1,1,MOP_UNCHAINED},{PORT_4,2,1,0}},0},
   {{"vmovlps", {OP_XMM, OP_NON, OP_NON, OP_MEC}}, 2, {{PORT_23,1,1,MOP_UNCHAINED},{PORT_4,2,1,0}},0},

/* ==================== VMOVHPS ==================== */

   {{"vmovhps", {OP_XMM, OP_NON, OP_NON, OP_MEM}}, 2, {{PORT_237,1,1,MOP_UNCHAINED},{PORT_4,2,1,0}},0},
   {{"vmovhps", {OP_XMM, OP_NON, OP_NON, OP_MEC}}, 2, {{PORT_23,1,1,MOP_UNCHAINED},{PORT_4,2,1,0}},0},

/* ==================== VMOVDQA (Выровненный доступ) ==================== */
/* 128-битные версии (XMM) */
   {{"vmovdqa", {OP_XMM, OP_NON, OP_NON, OP_XMM}}, 0, {}},
   {{"vmovdqa", {OP_MEM, OP_NON, OP_NON, OP_XMM}}, 1, {{PORT_23,6,1,0}},0},
   {{"vmovdqa", {OP_MEC, OP_NON, OP_NON, OP_XMM}}, 1, {{PORT_23,6,1,0}},0},
   {{"vmovdqa", {OP_XMM, OP_NON, OP_NON, OP_MEM}}, 2, {{PORT_237,1,1,MOP_UNCHAINED},{PORT_4,2,1,0}},0},
   {{"vmovdqa", {OP_XMM, OP_NON, OP_NON, OP_MEC}}, 2, {{PORT_23,1,1,MOP_UNCHAINED},{PORT_4,2,1,0}},0},
/* 256-битные версии (YMM) */
   {{"vmovdqa", {OP_YMM, OP_NON, OP_NON, OP_YMM}}, 0, {}},
   {{"vmovdqa", {OP_MEM, OP_NON, OP_NON, OP_YMM}}, 1, {{PORT_23,7,1,0}},0},
   {{"vmovdqa", {OP_MEC, OP_NON, OP_NON, OP_YMM}}, 1, {{PORT_23,7,1,0}},0},
   {{"vmovdqa", {OP_YMM, OP_NON, OP_NON, OP_MEM}}, 2, {{PORT_237,1,1,MOP_UNCHAINED},{PORT_4,2,1,0}},0},
   {{"vmovdqa", {OP_YMM, OP_NON, OP_NON, OP_MEC}}, 2, {{PORT_23,1,1,MOP_UNCHAINED},{PORT_4,2,1,0}},0},
	
/* ==================== MOVSXD / MOVSLQ ==================== */
	{{"movsxd", {OP_REG, OP_NON, OP_NON, OP_REG}}, 1, {{PORT_06,1,1,0}},0},
	{{"movsxd", {OP_MEM, OP_NON, OP_NON, OP_REG}}, 1, {{PORT_23,5,1,0}},0},
	{{"movsxd", {OP_MEC, OP_NON, OP_NON, OP_REG}}, 1, {{PORT_23,5,1,0}},0},
	{{"movslq", {OP_REG, OP_NON, OP_NON, OP_REG}}, 1, {{PORT_06,1,1,0}},0},
	{{"movslq", {OP_MEM, OP_NON, OP_NON, OP_REG}}, 1, {{PORT_23,5,1,0}},0},
	{{"movslq", {OP_MEC, OP_NON, OP_NON, OP_REG}}, 1, {{PORT_23,5,1,0}},0},	
	

/* ==================== VPERMD ==================== */
	{{"vpermd", {OP_YMM, OP_YMM, OP_NON, OP_YMM}}, 1, {{PORT_5,3,1,0}},0},
	{{"vpermd", {OP_YMM, OP_MEM, OP_NON, OP_YMM}}, 2, {{PORT_23,7,1,0},{PORT_5,3,1,0}},0},
	{{"vpermd", {OP_YMM, OP_MEC, OP_NON, OP_YMM}}, 2, {{PORT_23,7,1,0},{PORT_5,3,1,0}},0},

/* ==================== VPBLENDVB ==================== */
/* 128-битные версии (XMM) */
   {{"vpblendvb", {OP_XMM, OP_XMM, OP_XMM, OP_XMM}}, 2, {{PORT_015,1,2,0}},0},
   {{"vpblendvb", {OP_XMM, OP_MEM, OP_XMM, OP_XMM}}, 3, {{PORT_23,6,1,0},{PORT_015,1,2,0}},0},
   {{"vpblendvb", {OP_XMM, OP_MEC, OP_XMM, OP_XMM}}, 3, {{PORT_23,6,1,0},{PORT_015,1,2,0}},0},
    /* 256-битные версии (YMM) */
   {{"vpblendvb", {OP_YMM, OP_YMM, OP_YMM, OP_YMM}}, 2, {{PORT_015,1,2,0}},0},
   {{"vpblendvb", {OP_YMM, OP_MEM, OP_YMM, OP_YMM}}, 3, {{PORT_23,7,1,0},{PORT_015,1,2,0}},0},
   {{"vpblendvb", {OP_YMM, OP_MEC, OP_YMM, OP_YMM}}, 3, {{PORT_23,7,1,0},{PORT_015,1,2,0}},0},

/* ==================== VPGATHERDD ==================== */
/* 128-битная версия (XMM - сборка 4 элементов) */
   {{"vpgatherdd", {OP_XMM, OP_MEM, OP_NON, OP_XMM}}, 4, {{PORT_0,1,1,0},{PORT_015,1,1,0},{PORT_23,17,4,0},{ PORT_5,   1,  1, 0 }},0},
   {{"vpgatherdd", {OP_XMM, OP_MEC, OP_NON, OP_XMM}}, 4, {{PORT_0,1,1,0},{PORT_015,1,1,0},{PORT_23,17,4,0},{ PORT_5,   1,  1, 0 }},0},
/* 256-битная версия (YMM - сборка 8 элементов) */
   {{"vpgatherdd", {OP_YMM, OP_MEM, OP_NON, OP_YMM}}, 4, {{PORT_0,1,1,0},{PORT_015,1,1,0},{PORT_23,21,8,0},{ PORT_5,   1,  1, 0 }},0},
   {{"vpgatherdd", {OP_YMM, OP_MEC, OP_NON, OP_YMM}}, 4, {{PORT_0,1,1,0},{PORT_015,1,1,0},{PORT_23,21,8,0},{ PORT_5,   1,  1, 0 }},0},

/* ==================== VPAND ==================== */
/* 128-битные версии (XMM) */
   {{"vpand", {OP_XMM, OP_XMM, OP_NON, OP_XMM}}, 1, {{PORT_015,1,1,0}},0},
   {{"vpand", {OP_XMM, OP_MEM, OP_NON, OP_XMM}}, 2, {{PORT_23,6,1,0},{PORT_015,1,1,0}},0},
   {{"vpand", {OP_XMM, OP_MEC, OP_NON, OP_XMM}}, 2, {{PORT_23,6,1,0},{PORT_015,1,1,0}},0},
   {{"vpand", {OP_MEM, OP_XMM, OP_NON, OP_XMM}}, 2, {{PORT_23,6,1,0},{PORT_015,1,1,0}},0},
   {{"vpand", {OP_MEC, OP_XMM, OP_NON, OP_XMM}}, 2, {{PORT_23,6,1,0},{PORT_015,1,1,0}},0},
/* 256-битные версии (YMM) */
   {{"vpand", {OP_YMM, OP_YMM, OP_NON, OP_YMM}}, 1, {{PORT_015,1,1,0}},0},
   {{"vpand", {OP_YMM, OP_MEM, OP_NON, OP_YMM}}, 2, {{PORT_23,7,1,0},{PORT_015,1,1,0}},0},
   {{"vpand", {OP_YMM, OP_MEC, OP_NON, OP_YMM}}, 2, {{PORT_23,7,1,0},{PORT_015,1,1,0}},0},
   {{"vpand", {OP_MEM, OP_YMM, OP_NON, OP_YMM}}, 2, {{PORT_23,7,1,0},{PORT_015,1,1,0}},0},
   {{"vpand", {OP_MEC, OP_YMM, OP_NON, OP_YMM}}, 2, {{PORT_23,7,1,0},{PORT_015,1,1,0}},0},

/* ==================== VPOR ==================== */
/* 128-битные версии (XMM) */
   {{"vpor", {OP_XMM, OP_XMM, OP_NON, OP_XMM}}, 1, {{PORT_015,1,1,0}},0},
   {{"vpor", {OP_XMM, OP_MEM, OP_NON, OP_XMM}}, 2, {{PORT_23,6,1,0},{PORT_015,1,1,0}},0},
   {{"vpor", {OP_XMM, OP_MEC, OP_NON, OP_XMM}}, 2, {{PORT_23,6,1,0},{PORT_015,1,1,0}},0},
/* 256-битные версии (YMM) */
   {{"vpor", {OP_YMM, OP_YMM, OP_NON, OP_YMM}}, 1, {{PORT_015,1,1,0}},0},
   {{"vpor", {OP_YMM, OP_MEM, OP_NON, OP_YMM}}, 2, {{PORT_23,7,1,0},{PORT_015,1,1,0}},0},
   {{"vpor", {OP_YMM, OP_MEC, OP_NON, OP_YMM}}, 2, {{PORT_23,7,1,0},{PORT_015,1,1,0}},0},

/* ==================== VPXOR ==================== */
/* 128-битные версии (XMM) */
   {{"vpxor", {OP_XMM, OP_XMM, OP_NON, OP_XMM}}, 1, {{PORT_015,1,1,0}},0},
   {{"vpxor", {OP_XMM, OP_MEM, OP_NON, OP_XMM}}, 2, {{PORT_23,6,1,0},{PORT_015,1,1,0}},0},
   {{"vpxor", {OP_XMM, OP_MEC, OP_NON, OP_XMM}}, 2, {{PORT_23,6,1,0},{PORT_015,1,1,0}},0},
/* 256-битные версии (YMM) */
   {{"vpxor", {OP_YMM, OP_YMM, OP_NON, OP_YMM}}, 1, {{PORT_015,1,1,0}},0},
   {{"vpxor", {OP_YMM, OP_MEM, OP_NON, OP_YMM}}, 2, {{PORT_23,7,1,0},{PORT_015,1,1,0}},0},
   {{"vpxor", {OP_YMM, OP_MEC, OP_NON, OP_YMM}}, 2, {{PORT_23,7,1,0},{PORT_015,1,1,0}},0},

/* ==================== VPADDD ==================== */
/* 128-битные версии (XMM) */
   {{"vpaddd", {OP_XMM, OP_XMM, OP_NON, OP_XMM}}, 1, {{PORT_015,1,1,0}},0},
   {{"vpaddd", {OP_XMM, OP_MEM, OP_NON, OP_XMM}}, 2, {{PORT_23,6,1,0},{PORT_015,1,1,0}},0},
   {{"vpaddd", {OP_XMM, OP_MEC, OP_NON, OP_XMM}}, 2, {{PORT_23,6,1,0},{PORT_015,1,1,0}},0},
   {{"vpaddd", {OP_MEM, OP_XMM, OP_NON, OP_XMM}}, 2, {{PORT_23,6,1,0},{PORT_015,1,1,0}},0},
   {{"vpaddd", {OP_MEC, OP_XMM, OP_NON, OP_XMM}}, 2, {{PORT_23,6,1,0},{PORT_015,1,1,0}},0},
/* 256-битные версии (YMM) */
   {{"vpaddd", {OP_YMM, OP_YMM, OP_NON, OP_YMM}}, 1, {{PORT_015,1,1,0}},0},
   {{"vpaddd", {OP_YMM, OP_MEM, OP_NON, OP_YMM}}, 2, {{PORT_23,7,1,0},{PORT_015,1,1,0}},0},
   {{"vpaddd", {OP_YMM, OP_MEC, OP_NON, OP_YMM}}, 2, {{PORT_23,7,1,0},{PORT_015,1,1,0}},0},
   {{"vpaddd", {OP_MEM, OP_YMM, OP_NON, OP_YMM}}, 2, {{PORT_23,7,1,0},{PORT_015,1,1,0}},0},
   {{"vpaddd", {OP_MEC, OP_YMM, OP_NON, OP_YMM}}, 2, {{PORT_23,7,1,0},{PORT_015,1,1,0}},0},

/* ==================== VPADDQ ==================== */
/* 128-битные версии (XMM) */
   {{"vpaddq", {OP_XMM, OP_XMM, OP_NON, OP_XMM}}, 1, {{PORT_015,1,1,0}},0},
   {{"vpaddq", {OP_XMM, OP_MEM, OP_NON, OP_XMM}}, 2, {{PORT_23,6,1,0},{PORT_015,1,1,0}},0},
   {{"vpaddq", {OP_XMM, OP_MEC, OP_NON, OP_XMM}}, 2, {{PORT_23,6,1,0},{PORT_015,1,1,0}},0},
/* 256-битные версии (YMM) */
   {{"vpaddq", {OP_YMM, OP_YMM, OP_NON, OP_YMM}}, 1, {{PORT_015,1,1,0}},0},
   {{"vpaddq", {OP_YMM, OP_MEM, OP_NON, OP_YMM}}, 2, {{PORT_23,7,1,0},{PORT_015,1,1,0}},0},
   {{"vpaddq", {OP_YMM, OP_MEC, OP_NON, OP_YMM}}, 2, {{PORT_23,7,1,0},{PORT_015,1,1,0}},0},

/* ==================== VPSLLD ==================== */
/* 128-битные версии (XMM) */
   {{"vpslld", {OP_VAL, OP_XMM, OP_NON, OP_XMM}}, 1, {{PORT_01,1,1,0}},0},
   {{"vpslld", {OP_VAL, OP_MEM, OP_NON, OP_XMM}}, 2, {{PORT_23,6,1,0},{PORT_01,1,1,0}},0},
   {{"vpslld", {OP_VAL, OP_MEC, OP_NON, OP_XMM}}, 2, {{PORT_23,6,1,0},{PORT_01,1,1,0}},0},
/* 256-битные версии (YMM) */
   {{"vpslld", {OP_VAL, OP_YMM, OP_NON, OP_YMM}}, 1, {{PORT_01,1,1,0}},0},
   {{"vpslld", {OP_VAL, OP_MEM, OP_NON, OP_YMM}}, 2, {{PORT_23,7,1,0},{PORT_01,1,1,0}},0},
   {{"vpslld", {OP_VAL, OP_MEC, OP_NON, OP_YMM}}, 2, {{PORT_23,7,1,0},{PORT_01,1,1,0}},0},

/* ==================== VPSLLQ ==================== */
/* 128-битные версии (XMM) */
   {{"vpsllq", {OP_VAL, OP_XMM, OP_NON, OP_XMM}}, 1, {{PORT_01,1,1,0}},0},
   {{"vpsllq", {OP_VAL, OP_MEM, OP_NON, OP_XMM}}, 2, {{PORT_23,6,1,0},{PORT_01,1,1,0}},0},
   {{"vpsllq", {OP_VAL, OP_MEC, OP_NON, OP_XMM}}, 2, {{PORT_23,6,1,0},{PORT_01,1,1,0}},0},
/* 256-битные версии (YMM) */
   {{"vpsllq", {OP_VAL, OP_YMM, OP_NON, OP_YMM}}, 1, {{PORT_01,1,1,0}},0},
   {{"vpsllq", {OP_VAL, OP_MEM, OP_NON, OP_YMM}}, 2, {{PORT_23,7,1,0},{PORT_01,1,1,0}},0},
   {{"vpsllq", {OP_VAL, OP_MEC, OP_NON, OP_YMM}}, 2, {{PORT_23,7,1,0},{PORT_01,1,1,0}},0},

/* ==================== JMP ==================== */
   {{"jmp", {OP_NON, OP_NON, OP_NON, OP_NON}}, 1, {{PORT_6,1,1,0}},0},

/* ==================== VPSRLD ==================== */
/* 128-битные версии (XMM) */
   {{"vpsrld", {OP_XMM, OP_VAL, OP_NON, OP_XMM}}, 1, {{PORT_01,1,1,0}},0},
   {{"vpsrld", {OP_MEM, OP_VAL, OP_NON, OP_XMM}}, 2, {{PORT_23,6,1,0},{PORT_01,1,1,0}},0},
   {{"vpsrld", {OP_MEC, OP_VAL, OP_NON, OP_XMM}}, 2, {{PORT_23,6,1,0},{PORT_01,1,1,0}},0},
/* 256-битные версии (YMM) */
   {{"vpsrld", {OP_YMM, OP_VAL, OP_NON, OP_YMM}}, 1, {{PORT_01,1,1,0}},0},
   {{"vpsrld", {OP_MEM, OP_VAL, OP_NON, OP_YMM}}, 2, {{PORT_23,7,1,0},{PORT_01,1,1,0}},0},
   {{"vpsrld", {OP_MEC, OP_VAL, OP_NON, OP_YMM}}, 2, {{PORT_23,7,1,0},{PORT_01,1,1,0}},0},

/* ==================== VPMULLD ==================== */
/* 128-битные версии (XMM) */
   {{"vpmulld", {OP_XMM, OP_XMM, OP_NON, OP_XMM}}, 2, {{PORT_01,5,1,0},{PORT_01,5,1,0}},0},
   {{"vpmulld", {OP_XMM, OP_MEM, OP_NON, OP_XMM}}, 3, {{PORT_23,6,1,0},{PORT_01,5,1,0},{PORT_01,5,1,0}},0},
   {{"vpmulld", {OP_XMM, OP_MEC, OP_NON, OP_XMM}}, 3, {{PORT_23,6,1,0},{PORT_01,5,1,0},{PORT_01,5,1,0}},0},
/* 256-битные версии (YMM) */
   {{"vpmulld", {OP_YMM, OP_YMM, OP_NON, OP_YMM}}, 3, {{PORT_01,4,1,0},{PORT_01,3,1,0},{PORT_01,3,1,0}},0},
   {{"vpmulld", {OP_YMM, OP_MEM, OP_NON, OP_YMM}}, 4, {{PORT_23,7,1,0},{PORT_01,4,1,0},{PORT_01,3,1,0},{PORT_01,3,1,0}},0},
   {{"vpmulld", {OP_YMM, OP_MEC, OP_NON, OP_YMM}}, 4, {{PORT_23,7,1,0},{PORT_01,4,1,0},{PORT_01,3,1,0},{PORT_01,3,1,0}},0},

/* ==================== VPMULUDQ (AVX2 Векторное умножение) ==================== */
/* 128-битные версии (XMM) */
   {{"vpmuludq", {OP_XMM, OP_XMM, OP_NON, OP_XMM}}, 1, {{PORT_0,5,1,0}},0},
   {{"vpmuludq", {OP_XMM, OP_MEM, OP_NON, OP_XMM}}, 2, {{PORT_23,6,1,0},{PORT_0,5,1,0}},0},
   {{"vpmuludq", {OP_XMM, OP_MEC, OP_NON, OP_XMM}}, 2, {{PORT_23,6,1,0},{PORT_0,5,1,0}},0},
/* 256-битные версии (YMM) */
   {{"vpmuludq", {OP_YMM, OP_YMM, OP_NON, OP_YMM}}, 1, {{PORT_0,5,1,0}},0},
   {{"vpmuludq", {OP_YMM, OP_MEM, OP_NON, OP_YMM}}, 2, {{PORT_23,7,1,0},{PORT_0,5,1,0}},0},
   {{"vpmuludq", {OP_YMM, OP_MEC, OP_NON, OP_YMM}}, 2, {{PORT_23,7,1,0},{PORT_0,5,1,0}},0},
	
/* ==================== VPCMPEQD ==================== */
/* 128-битные версии (XMM) */
   {{"vpcmpeqd", {OP_XMM, OP_XMM, OP_NON, OP_XMM}}, 1, {{PORT_015,1,1,0}},0},
   {{"vpcmpeqd", {OP_XMM, OP_MEM, OP_NON, OP_XMM}}, 2, {{PORT_23,6,1,0},{PORT_015,1,1,0}},0},
   {{"vpcmpeqd", {OP_XMM, OP_MEC, OP_NON, OP_XMM}}, 2, {{PORT_23,6,1,0},{PORT_015,1,1,0}},0},
/* 256-битные версии (YMM) */
   {{"vpcmpeqd", {OP_YMM, OP_YMM, OP_NON, OP_YMM}}, 1, {{PORT_015,1,1,0}},0},
   {{"vpcmpeqd", {OP_YMM, OP_MEM, OP_NON, OP_YMM}}, 2, {{PORT_23,7,1,0},{PORT_015,1,1,0}},0},
   {{"vpcmpeqd", {OP_YMM, OP_MEC, OP_NON, OP_YMM}}, 2, {{PORT_23,7,1,0},{PORT_015,1,1,0}},0},

/* ==================== VMOVMSKPS ==================== */
/* 128-битная версия (XMM) */
   {{"vmovmskps", {OP_XMM, OP_NON, OP_NON, OP_REG}}, 1, {{PORT_0,3,1,0}},0},
 /* 256-битная версия (YMM) */
   {{"vmovmskps", {OP_YMM, OP_NON, OP_NON, OP_REG}}, 1, {{PORT_0,3,1,0}},0},

/* ==================== SALQ ==================== */
   {{"salq", {OP_REG, OP_VAL, OP_NON, OP_REG}}, 1, {{PORT_06,1,1,0}},0},
   {{"salq", {OP_MEM, OP_VAL, OP_NON, OP_MEM}}, 4, {{PORT_23,4,1,0},{PORT_06,1,1,0},{PORT_237,1,1,MOP_UNCHAINED},{PORT_4,2,1,0}},0},
   {{"salq", {OP_MEC, OP_VAL, OP_NON, OP_MEC}}, 4, {{PORT_23,4,1,0},{PORT_06,1,1,0},{PORT_23,1,1,MOP_UNCHAINED},{PORT_4,2,1,0}},0},

/* ==================== VPMOVZXBD ==================== */
/* 128-битные версии (XMM) */
   {{"vpmovzxbd", {OP_XMM, OP_NON, OP_NON, OP_XMM}}, 1, {{PORT_015,3,1,0}},0},
   {{"vpmovzxbd", {OP_MEM, OP_NON, OP_NON, OP_XMM}}, 2, {{PORT_23,6,1,0},{PORT_015,3,1,0}},0},
   {{"vpmovzxbd", {OP_MEC, OP_NON, OP_NON, OP_XMM}}, 2, {{PORT_23,6,1,0},{PORT_015,3,1,0}},0},
/* 256-битные версии (YMM) */
   {{"vpmovzxbd", {OP_XMM, OP_NON, OP_NON, OP_YMM}}, 1, {{PORT_015,3,1,0}},0},
   {{"vpmovzxbd", {OP_MEM, OP_NON, OP_NON, OP_YMM}}, 2, {{PORT_23,7,1,0},{PORT_015,3,1,0}},0},
   {{"vpmovzxbd", {OP_MEC, OP_NON, OP_NON, OP_YMM}}, 2, {{PORT_23,7,1,0},{PORT_015,3,1,0}},0},

/* ==================== PDEP ==================== */
   {{"pdep", {OP_REG, OP_REG, OP_NON, OP_REG}}, 1, {{PORT_1,3,1,0}},0},
   {{"pdep", {OP_REG, OP_MEM, OP_NON, OP_REG}}, 2, {{PORT_23,4,1,0},{PORT_1,3,1,0}},0},
   {{"pdep", {OP_REG, OP_MEC, OP_NON, OP_REG}}, 2, {{PORT_23,4,1,0},{PORT_1,3,1,0}},0},

/* ==================== PEXT ==================== */
   {{"pext", {OP_REG, OP_REG, OP_NON, OP_REG}}, 1, {{PORT_1,3,1,0}},0},
   {{"pext", {OP_REG, OP_MEM, OP_NON, OP_REG}}, 2, {{PORT_23,4,1,0},{PORT_1,3,1,0}},0},
   {{"pext", {OP_REG, OP_MEC, OP_NON, OP_REG}}, 2, {{PORT_23,4,1,0},{PORT_1,3,1,0}},0},

/* ==================== POPCNT ==================== */
   {{"popcnt", {OP_REG, OP_NON, OP_NON, OP_REG}}, 1, {{PORT_1,3,1,0}},0},
   {{"popcnt", {OP_MEM, OP_NON, OP_NON, OP_REG}}, 2, {{PORT_23,4,1,0},{PORT_1,3,1,0}},0},
   {{"popcnt", {OP_MEC, OP_NON, OP_NON, OP_REG}}, 2, {{PORT_23,4,1,0},{PORT_1,3,1,0}},0},

/* ==================== CLTQ ==================== */
   {{"cltq", {OP_NON, OP_NON, OP_NON, OP_NON}}, 1, {{PORT_0156,1,1,0}},0},

/* ==================== CMPL ==================== */
   {{"cmpl", {OP_REG, OP_NON, OP_NON, OP_REG}}, 1, {{PORT_0156,1,1,0}},0},

/* ==================== SARL ==================== */
   {{"sarl", {OP_VAL, OP_NON, OP_NON, OP_REG}}, 1, {{PORT_06,1,1,0}},1},
   {{"sarl", {OP_VAL, OP_NON, OP_NON, OP_MEM}}, 4, {{PORT_23,4,1,0},{PORT_06,1,1,0},{PORT_237,1,1,MOP_UNCHAINED},{PORT_4,2,1,0}},1},
   {{"sarl", {OP_VAL, OP_NON, OP_NON, OP_MEC}}, 4, {{PORT_23,4,1,0},{PORT_06,1,1,0},{PORT_23,1,1,MOP_UNCHAINED},{PORT_4,2,1,0}},1},

/* ==================== SALQ ==================== */
   {{"salq", {OP_VAL, OP_NON, OP_NON, OP_REG}}, 1, {{PORT_06,1,1,0}},1},
   {{"salq", {OP_VAL, OP_NON, OP_NON, OP_MEM}}, 4, {{PORT_23,4,1,0},{PORT_06,1,1,0},{PORT_237,1,1,MOP_UNCHAINED},{PORT_4,2,1,0}},1},
   {{"salq", {OP_VAL, OP_NON, OP_NON, OP_MEC}}, 4, {{PORT_23,4,1,0},{PORT_06,1,1,0},{PORT_23,1,1,MOP_UNCHAINED},{PORT_4,2,1,0}},1},

/* ==================== SARQ ==================== */
   {{"sarq", {OP_VAL, OP_NON, OP_NON, OP_REG}}, 1, {{PORT_06,1,1,0}},1},
   {{"sarq", {OP_VAL, OP_NON, OP_NON, OP_MEM}}, 4, {{PORT_23,4,1,0},{PORT_06,1,1,0},{PORT_237,1,1,MOP_UNCHAINED},{PORT_4,2,1,0}},1},
   {{"sarq", {OP_VAL, OP_NON, OP_NON, OP_MEC}}, 4, {{PORT_23,4,1,0},{PORT_06,1,1,0},{PORT_23,1,1,MOP_UNCHAINED},{PORT_4,2,1,0}},1},

/* ==================== SHRQ ==================== */
   {{"shrq", {OP_VAL, OP_NON, OP_NON, OP_REG}}, 1, {{PORT_06,1,1,0}},1},
   {{"shrq", {OP_VAL, OP_NON, OP_NON, OP_MEM}}, 4, {{PORT_23,4,1,0},{PORT_06,1,1,0},{PORT_237,1,1,MOP_UNCHAINED},{PORT_4,2,1,0}},1},
   {{"shrq", {OP_VAL, OP_NON, OP_NON, OP_MEC}}, 4, {{PORT_23,4,1,0},{PORT_06,1,1,0},{PORT_23,1,1,MOP_UNCHAINED},{PORT_4,2,1,0}},1},

/* ==================== INCL ==================== */
   {{"incl", {OP_NON, OP_NON, OP_NON, OP_REG}}, 1, {{PORT_0156,1,1,0}},1},
   {{"incl", {OP_NON, OP_NON, OP_NON, OP_MEM}}, 4, {{PORT_23,4,1,0},{PORT_0156,1,1,0},{PORT_237,1,1,MOP_UNCHAINED},{PORT_4,2,1,0}},1},
   {{"incl", {OP_NON, OP_NON, OP_NON, OP_MEC}}, 4, {{PORT_23,4,1,0},{PORT_0156,1,1,0},{PORT_23,1,1,MOP_UNCHAINED},{PORT_4,2,1,0}},1},

/* ==================== INCQ ==================== */
   {{"incq", {OP_NON, OP_NON, OP_NON, OP_REG}}, 1, {{PORT_0156,1,1,0}},1},
   {{"incq", {OP_NON, OP_NON, OP_NON, OP_MEM}}, 4, {{PORT_23,4,1,0},{PORT_0156,1,1,0},{PORT_237,1,1,MOP_UNCHAINED},{PORT_4,2,1,0}},1},
   {{"incq", {OP_NON, OP_NON, OP_NON, OP_MEC}}, 4, {{PORT_23,4,1,0},{PORT_0156,1,1,0},{PORT_23,1,1,MOP_UNCHAINED},{PORT_4,2,1,0}},1},

/* ==================== CMOVA ==================== */
   {{"cmova", {OP_REG, OP_NON, OP_NON, OP_REG}}, 2, {{PORT_0156,2,2,0}},1},
   {{"cmova", {OP_MEM, OP_NON, OP_NON, OP_REG}}, 3, {{PORT_23,4,1,0},{PORT_0156,2,2,0}},1},
   {{"cmova", {OP_MEC, OP_NON, OP_NON, OP_REG}}, 3, {{PORT_23,4,1,0},{PORT_0156,2,2,0}},1},

/* ==================== VPBROADCASTQ ==================== */
/* 128-битные версии (XMM) */
   {{"vpbroadcastq", {OP_XMM, OP_NON, OP_NON, OP_XMM}}, 1, {{PORT_5,1,1,0}},0},
   {{"vpbroadcastq", {OP_MEM, OP_NON, OP_NON, OP_XMM}}, 1, {{PORT_23,6,1,0}},0},
   {{"vpbroadcastq", {OP_MEC, OP_NON, OP_NON, OP_XMM}}, 1, {{PORT_23,6,1,0}},0},
/* 256-битные версии (YMM) */
   {{"vpbroadcastq", {OP_XMM, OP_NON, OP_NON, OP_YMM}}, 1, {{PORT_5,3,1,0}},0},
   {{"vpbroadcastq", {OP_MEM, OP_NON, OP_NON, OP_YMM}}, 1, {{PORT_23,7,1,0}},0},
   {{"vpbroadcastq", {OP_MEC, OP_NON, OP_NON, OP_YMM}}, 1, {{PORT_23,7,1,0}},0},

/* ==================== VBROADCASTSS ==================== */
/* 128-битные версии (XMM) */
   {{"vbroadcastss", {OP_XMM, OP_NON, OP_NON, OP_XMM}}, 1, {{PORT_5,3,1,0}},0},
   {{"vbroadcastss", {OP_MEM, OP_NON, OP_NON, OP_XMM}}, 1, {{PORT_23,6,1,0}},0},
   {{"vbroadcastss", {OP_MEC, OP_NON, OP_NON, OP_XMM}}, 1, {{PORT_23,6,1,0}},0},
/* 256-битные версии (YMM) */
   {{"vbroadcastss", {OP_XMM, OP_NON, OP_NON, OP_YMM}}, 1, {{PORT_5,3,1,0}},0},
   {{"vbroadcastss", {OP_MEM, OP_NON, OP_NON, OP_YMM}}, 1, {{PORT_23,7,1,0}},0},
   {{"vbroadcastss", {OP_MEC, OP_NON, OP_NON, OP_YMM}}, 1, {{PORT_23,7,1,0}},0},
	
/* ==================== VFMADD231ps ==================== */
/* 256-битные версии (YMM) */
   {{"vfmadd231ps", {OP_YMM, OP_YMM, OP_NON, OP_YMM}}, 1, {{PORT_01,4,1,0}},1},

/* ==================== VUNPCKLPS ==================== */
/* 128-битные версии (XMM) */
   {{"vunpcklps", {OP_XMM, OP_XMM, OP_NON, OP_XMM}}, 1, {{PORT_5,1,1,0}},1},
/* 256-битные версии (YMM) */
   {{"vunpcklps", {OP_YMM, OP_YMM, OP_NON, OP_YMM}}, 1, {{PORT_5,1,1,0}},1},

/* ==================== VUNPCKHPS ==================== */
/* 128-битные версии (XMM) */
   {{"vunpckhps", {OP_XMM, OP_XMM, OP_NON, OP_XMM}}, 1, {{PORT_5,1,1,0}},1},
/* 256-битные версии (YMM) */
   {{"vunpckhps", {OP_YMM, OP_YMM, OP_NON, OP_YMM}}, 1, {{PORT_5,1,1,0}},1},

/* ==================== VPSRLQ ==================== */
/* 128-битные версии (XMM) */
   {{"vpsrlq", {OP_VAL, OP_XMM, OP_NON, OP_XMM}}, 1, {{PORT_01,1,1,0}},0},
   {{"vpsrlq", {OP_VAL, OP_MEM, OP_NON, OP_XMM}}, 2, {{PORT_23,6,1,0},{PORT_01,1,1,0}},0},
   {{"vpsrlq", {OP_VAL, OP_MEC, OP_NON, OP_XMM}}, 2, {{PORT_23,6,1,0},{PORT_01,1,1,0}},0},
/* 256-битные версии (YMM) */
   {{"vpsrlq", {OP_VAL, OP_YMM, OP_NON, OP_YMM}}, 1, {{PORT_01,1,1,0}},0},
   {{"vpsrlq", {OP_VAL, OP_MEM, OP_NON, OP_YMM}}, 2, {{PORT_23,7,1,0},{PORT_01,1,1,0}},0},
   {{"vpsrlq", {OP_VAL, OP_MEC, OP_NON, OP_YMM}}, 2, {{PORT_23,7,1,0},{PORT_01,1,1,0}},0},

/* ==================== VPBROADCASTD ==================== */
/* 128-битные версии (XMM) */
   {{"vpbroadcastd", {OP_XMM, OP_NON, OP_NON, OP_XMM}}, 1, {{PORT_5,1,1,0}},0},
   {{"vpbroadcastd", {OP_MEM, OP_NON, OP_NON, OP_XMM}}, 1, {{PORT_23,6,1,0}},0},
   {{"vpbroadcastd", {OP_MEC, OP_NON, OP_NON, OP_XMM}}, 1, {{PORT_23,6,1,0}},0},
/* 256-битные версии (YMM) */
   {{"vpbroadcastd", {OP_XMM, OP_NON, OP_NON, OP_YMM}}, 1, {{PORT_5,3,1,0}},0},
   {{"vpbroadcastd", {OP_MEM, OP_NON, OP_NON, OP_YMM}}, 1, {{PORT_23,7,1,0}},0},
   {{"vpbroadcastd", {OP_MEC, OP_NON, OP_NON, OP_YMM}}, 1, {{PORT_23,7,1,0}},0},

/* ==================== VPBROADCASTB ==================== */
/* 128-битные версии (XMM) */
   {{"vpbroadcastb", {OP_XMM, OP_NON, OP_NON, OP_XMM}}, 1, {{PORT_5,1,1,0}},0},
   {{"vpbroadcastb", {OP_MEM, OP_NON, OP_NON, OP_XMM}}, 1, {{PORT_23,6,1,0}},0},
   {{"vpbroadcastb", {OP_MEC, OP_NON, OP_NON, OP_XMM}}, 1, {{PORT_23,6,1,0}},0},
/* 256-битные версии (YMM) */
   {{"vpbroadcastb", {OP_XMM, OP_NON, OP_NON, OP_YMM}}, 1, {{PORT_5,3,1,0}},0},
   {{"vpbroadcastb", {OP_MEM, OP_NON, OP_NON, OP_YMM}}, 1, {{PORT_23,7,1,0}},0},
   {{"vpbroadcastb", {OP_MEC, OP_NON, OP_NON, OP_YMM}}, 1, {{PORT_23,7,1,0}},0},

/* ==================== VPMULUDQ ==================== */
/* 128-битные версии (XMM) */
   {{"vpmuludq", {OP_XMM, OP_XMM, OP_NON, OP_XMM}}, 1, {{PORT_0,5,1,0}},0},
   {{"vpmuludq", {OP_XMM, OP_MEM, OP_NON, OP_XMM}}, 2, {{PORT_23,6,1,0},{PORT_0,5,1,0}},0},
   {{"vpmuludq", {OP_XMM, OP_MEC, OP_NON, OP_XMM}}, 2, {{PORT_23,6,1,0},{PORT_0,5,1,0}},0},
/* 256-битные версии (YMM) */
   {{"vpmuludq", {OP_YMM, OP_YMM, OP_NON, OP_YMM}}, 1, {{PORT_0,5,1,0}},0},
   {{"vpmuludq", {OP_YMM, OP_MEM, OP_NON, OP_YMM}}, 2, {{PORT_23,7,1,0},{PORT_0,5,1,0}},0},
   {{"vpmuludq", {OP_YMM, OP_MEC, OP_NON, OP_YMM}}, 2, {{PORT_23,7,1,0},{PORT_0,5,1,0}},0},
	
/* ==================== VPMOVZXDQ ==================== */
/* 128-битные версии (XMM) */
   {{"vpmovzxdq", {OP_XMM, OP_NON, OP_NON, OP_XMM}}, 1, {{PORT_015,3,1,0}},0},
   {{"vpmovzxdq", {OP_MEM, OP_NON, OP_NON, OP_XMM}}, 2, {{PORT_23,6,1,0},{PORT_015,3,1,0}},0},
   {{"vpmovzxdq", {OP_MEC, OP_NON, OP_NON, OP_XMM}}, 2, {{PORT_23,6,1,0},{PORT_015,3,1,0}},0},
/* 256-битные версии (YMM) */
   {{"vpmovzxdq", {OP_XMM, OP_NON, OP_NON, OP_YMM}}, 1, {{PORT_015,3,1,0}},0},
   {{"vpmovzxdq", {OP_MEM, OP_NON, OP_NON, OP_YMM}}, 2, {{PORT_23,7,1,0},{PORT_015,3,1,0}},0},
   {{"vpmovzxdq", {OP_MEC, OP_NON, OP_NON, OP_YMM}}, 2, {{PORT_23,7,1,0},{PORT_015,3,1,0}},0},

/* ==================== VPMOVSXDQ ==================== */
/* 128-битные версии (XMM) */
   {{"vpmovsxdq", {OP_XMM, OP_NON, OP_NON, OP_XMM}}, 1, {{PORT_015,3,1,0}},0},
   {{"vpmovsxdq", {OP_MEM, OP_NON, OP_NON, OP_XMM}}, 2, {{PORT_23,6,1,0},{PORT_015,3,1,0}},0},
   {{"vpmovsxdq", {OP_MEC, OP_NON, OP_NON, OP_XMM}}, 2, {{PORT_23,6,1,0},{PORT_015,3,1,0}},0},
/* 256-битные версии (YMM) */
   {{"vpmovsxdq", {OP_XMM, OP_NON, OP_NON, OP_YMM}}, 1, {{PORT_015,3,1,0}},0},
   {{"vpmovsxdq", {OP_MEM, OP_NON, OP_NON, OP_YMM}}, 2, {{PORT_23,7,1,0},{PORT_015,3,1,0}},0},
   {{"vpmovsxdq", {OP_MEC, OP_NON, OP_NON, OP_YMM}}, 2, {{PORT_23,7,1,0},{PORT_015,3,1,0}},0},

/* ==================== VPCMPEQB ==================== */
/* 128-битные версии (XMM) */
   {{"vpcmpeqb", {OP_XMM, OP_XMM, OP_NON, OP_XMM}}, 1, {{PORT_015,1,1,0}},0},
   {{"vpcmpeqb", {OP_XMM, OP_MEM, OP_NON, OP_XMM}}, 2, {{PORT_23,6,1,0},{PORT_015,1,1,0}},0},
   {{"vpcmpeqb", {OP_XMM, OP_MEC, OP_NON, OP_XMM}}, 2, {{PORT_23,6,1,0},{PORT_015,1,1,0}},0},
/* 256-битные версии (YMM) */
   {{"vpcmpeqb", {OP_YMM, OP_YMM, OP_NON, OP_YMM}}, 1, {{PORT_015,1,1,0}},0},
   {{"vpcmpeqb", {OP_YMM, OP_MEM, OP_NON, OP_YMM}}, 2, {{PORT_23,7,1,0},{PORT_015,1,1,0}},0},
   {{"vpcmpeqb", {OP_YMM, OP_MEC, OP_NON, OP_YMM}}, 2, {{PORT_23,7,1,0},{PORT_015,1,1,0}},0},

/* ==================== NOTL ==================== */
   {{"notl", {OP_REG, OP_NON, OP_NON, OP_REG}}, 1, {{PORT_0156,1,1,0}},0},
   {{"notl", {OP_MEM, OP_NON, OP_NON, OP_NON}}, 4, {{PORT_23,4,1,0},{PORT_0156,1,1,0},{PORT_237,1,1,MOP_UNCHAINED},{PORT_4,2,1,0}},0},
   {{"notl", {OP_MEC, OP_NON, OP_NON, OP_NON}}, 4, {{PORT_23,4,1,0},{PORT_0156,1,1,0},{PORT_23,1,1,MOP_UNCHAINED},{PORT_4,2,1,0}},0},

/* ==================== PREFETCHT2 ==================== */
   {{"prefetcht2", {OP_MEM, OP_NON, OP_NON, OP_NON}}, 1, {{PORT_23,0,1,0}},0},
   {{"prefetcht2", {OP_MEC, OP_NON, OP_NON, OP_NON}}, 1, {{PORT_23,0,1,0}},0},
	
/* ==================== VPERMQ ==================== */
   {{"vpermq", {OP_YMM, OP_VAL, OP_NON, OP_YMM}}, 1, {{PORT_5,3,1,0}},0},
   {{"vpermq", {OP_MEM, OP_VAL, OP_NON, OP_YMM}}, 2, {{PORT_23,7,1,0},{PORT_5,3,1,0}},0},
   {{"vpermq", {OP_MEC, OP_VAL, OP_NON, OP_YMM}}, 2, {{PORT_23,7,1,0},{PORT_5,3,1,0}},0},

/* ==================== VPINSRD ==================== */
   {{"vpinsrd", {OP_XMM, OP_REG, OP_VAL, OP_XMM}}, 1, {{PORT_5,3,2,0}},0},
   {{"vpinsrd", {OP_XMM, OP_MEM, OP_VAL, OP_XMM}}, 2, {{PORT_23,6,1,0},{PORT_5,3,1,0}},0},
   {{"vpinsrd", {OP_XMM, OP_MEC, OP_VAL, OP_XMM}}, 2, {{PORT_23,6,1,0},{PORT_5,3,1,0}},0},

/* ==================== NEGL ==================== */
   {{"negl", {OP_NON, OP_NON, OP_NON, OP_REG}}, 1, {{PORT_0156,1,1,0}},1},
   {{"negl", {OP_NON, OP_NON, OP_NON, OP_MEM}}, 4, {{PORT_23,4,1,0},{PORT_0156,1,1,0},{PORT_237,1,1,MOP_UNCHAINED},{PORT_4,2,1,0}},1},
   {{"negl", {OP_NON, OP_NON, OP_NON, OP_MEC}}, 4, {{PORT_23,4,1,0},{PORT_0156,1,1,0},{PORT_23,1,1,MOP_UNCHAINED},{PORT_4,2,1,0}},1},

/* ==================== BLSR ==================== */
   {{"blsr", {OP_REG, OP_NON, OP_NON, OP_REG}}, 1, {{PORT_0156,1,1,0}},0},
   {{"blsr", {OP_MEM, OP_NON, OP_NON, OP_REG}}, 2, {{PORT_23,4,1,0},{PORT_0156,1,1,0}},0},
   {{"blsr", {OP_MEC, OP_NON, OP_NON, OP_REG}}, 2, {{PORT_23,4,1,0},{PORT_0156,1,1,0}},0},

/* ==================== SETLE ==================== */
   {{"setle", {OP_NON, OP_NON, OP_NON, OP_REG}}, 1, {{PORT_0156,1,1,0}},1},

/* ==================== SETNE ==================== */
   {{"setne", {OP_NON, OP_NON, OP_NON, OP_REG}}, 1, {{PORT_0156,1,1,0}},1},

/* ==================== IMULL ==================== */
   {{"imull", {OP_REG, OP_REG, OP_NON, OP_REG}}, 1, {{PORT_1,3,1,0}},0},
   {{"imull", {OP_REG, OP_MEM, OP_NON, OP_REG}}, 2, {{PORT_23,4,1,0},{PORT_1,3,1,0}},0},
   {{"imull", {OP_REG, OP_MEC, OP_NON, OP_REG}}, 2, {{PORT_23,4,1,0},{PORT_1,3,1,0}},0},

/* ==================== TZCNT ==================== */
   {{"tzcnt", {OP_REG, OP_NON, OP_NON, OP_REG}}, 1, {{PORT_1,3,1,0}},0},
   {{"tzcnt", {OP_MEM, OP_NON, OP_NON, OP_REG}}, 2, {{PORT_23,4,1,0},{PORT_1,3,1,0}},0},
   {{"tzcnt", {OP_MEC, OP_NON, OP_NON, OP_REG}}, 2, {{PORT_23,4,1,0},{PORT_1,3,1,0}},0},

/* ==================== VPSHUFB ==================== */
/* 128-битные версии (XMM) */
   {{"vpshufb", {OP_XMM, OP_XMM, OP_NON, OP_XMM}}, 1, {{PORT_5,1,1,0}},0},
   {{"vpshufb", {OP_XMM, OP_MEM, OP_NON, OP_XMM}}, 2, {{PORT_23,6,1,0},{PORT_5,1,1,0}},0},
   {{"vpshufb", {OP_XMM, OP_MEC, OP_NON, OP_XMM}}, 2, {{PORT_23,6,1,0},{PORT_5,1,1,0}},0},
/* 256-битные версии (YMM) */
   {{"vpshufb", {OP_YMM, OP_YMM, OP_NON, OP_YMM}}, 1, {{PORT_5,1,1,0}},0},
   {{"vpshufb", {OP_YMM, OP_MEM, OP_NON, OP_YMM}}, 2, {{PORT_23,7,1,0},{PORT_5,1,1,0}},0},
   {{"vpshufb", {OP_YMM, OP_MEC, OP_NON, OP_YMM}}, 2, {{PORT_23,7,1,0},{PORT_5,1,1,0}},0},

/* ==================== VDIVSD ==================== */
   {{"vdivsd", {OP_XMM, OP_XMM, OP_NON, OP_XMM}}, 1, {{PORT_0,14,4,0}},0},
   {{"vdivsd", {OP_XMM, OP_MEM, OP_NON, OP_XMM}}, 2, {{PORT_23,4,1,0},{PORT_0,14,4,0}},0},
   {{"vdivsd", {OP_XMM, OP_MEC, OP_NON, OP_XMM}}, 2, {{PORT_23,4,1,0},{PORT_0,14,4,0}},0},

/* ==================== VPMULUDQ ==================== */
/* 128-битные версии (XMM) */
   {{"vpmuludq", {OP_XMM, OP_XMM, OP_NON, OP_XMM}}, 1, {{PORT_0,5,1,0}},0},
   {{"vpmuludq", {OP_XMM, OP_MEM, OP_NON, OP_XMM}}, 2, {{PORT_23,6,1,0},{PORT_0,5,1,0}},0},
   {{"vpmuludq", {OP_XMM, OP_MEC, OP_NON, OP_XMM}}, 2, {{PORT_23,6,1,0},{PORT_0,5,1,0}},0},
/* 256-битные версии (YMM) */
   {{"vpmuludq", {OP_YMM, OP_YMM, OP_NON, OP_YMM}}, 1, {{PORT_0,5,1,0}},0},
   {{"vpmuludq", {OP_YMM, OP_MEM, OP_NON, OP_YMM}}, 2, {{PORT_23,7,1,0},{PORT_0,5,1,0}},0},
   {{"vpmuludq", {OP_YMM, OP_MEC, OP_NON, OP_YMM}}, 2, {{PORT_23,7,1,0},{PORT_0,5,1,0}},0},

/* ==================== VPMULDQ ==================== */
/* 128-битные версии (XMM) */
   {{"vpmuldq", {OP_XMM, OP_XMM, OP_NON, OP_XMM}}, 1, {{PORT_0,5,1,0}},0},
   {{"vpmuldq", {OP_XMM, OP_MEM, OP_NON, OP_XMM}}, 2, {{PORT_23,6,1,0},{PORT_0,5,1,0}},0},
   {{"vpmuldq", {OP_XMM, OP_MEC, OP_NON, OP_XMM}}, 2, {{PORT_23,6,1,0},{PORT_0,5,1,0}},0},
/* 256-битные версии (YMM) */
   {{"vpmuldq", {OP_YMM, OP_YMM, OP_NON, OP_YMM}}, 1, {{PORT_0,5,1,0}},0},
   {{"vpmuldq", {OP_YMM, OP_MEM, OP_NON, OP_YMM}}, 2, {{PORT_23,7,1,0},{PORT_0,5,1,0}},0},
   {{"vpmuldq", {OP_YMM, OP_MEC, OP_NON, OP_YMM}}, 2, {{PORT_23,7,1,0},{PORT_0,5,1,0}},0},

/* ==================== VPMULLD ==================== */
/* 128-битные версии (XMM) */
   {{"vpmulld", {OP_XMM, OP_XMM, OP_NON, OP_XMM}}, 2, {{PORT_01,5,1,0},{PORT_01,5,1,0}},0},
   {{"vpmulld", {OP_XMM, OP_MEM, OP_NON, OP_XMM}}, 3, {{PORT_23,6,1,0},{PORT_01,5,1,0},{PORT_01,5,1,0}},0},
   {{"vpmulld", {OP_XMM, OP_MEC, OP_NON, OP_XMM}}, 3, {{PORT_23,6,1,0},{PORT_01,5,1,0},{PORT_01,5,1,0}},0},
/* 256-битные версии (YMM) */
   {{"vpmulld", {OP_YMM, OP_YMM, OP_NON, OP_YMM}}, 3, {{PORT_01,4,1,0},{PORT_01,3,1,0},{PORT_01,3,1,0}},0},
   {{"vpmulld", {OP_YMM, OP_MEM, OP_NON, OP_YMM}}, 4, {{PORT_23,7,1,0},{PORT_01,4,1,0},{PORT_01,3,1,0},{PORT_01,3,1,0}},0},
   {{"vpmulld", {OP_YMM, OP_MEC, OP_NON, OP_YMM}}, 4, {{PORT_23,7,1,0},{PORT_01,4,1,0},{PORT_01,3,1,0},{PORT_01,3,1,0}},0},

/* ==================== VPHADDD ==================== */
/* 128-битные версии (XMM) */
   {{"vphaddd", {OP_XMM, OP_XMM, OP_NON, OP_XMM}}, 3, {{PORT_015,1,1,0},{PORT_015,1,1,0},{PORT_015,1,1,0}},0},
   {{"vphaddd", {OP_XMM, OP_MEM, OP_NON, OP_XMM}}, 4, {{PORT_23,6,1,0},{PORT_015,1,1,0},{PORT_015,1,1,0},{PORT_015,1,1,0}},0},
   {{"vphaddd", {OP_XMM, OP_MEC, OP_NON, OP_XMM}}, 4, {{PORT_23,6,1,0},{PORT_015,1,1,0},{PORT_015,1,1,0},{PORT_015,1,1,0}},0},
/* 256-битные версии (YMM) */
   {{"vphaddd", {OP_YMM, OP_YMM, OP_NON, OP_YMM}}, 5, {{PORT_015,1,1,0},{PORT_015,1,1,0},{PORT_015,1,1,0},{PORT_015,1,1,0},{PORT_015,1,1,0}},0},
   {{"vphaddd", {OP_YMM, OP_MEM, OP_NON, OP_YMM}}, 6, {{PORT_23,7,1,0},{PORT_015,1,1,0},{PORT_015,1,1,0},{PORT_015,1,1,0},{PORT_015,1,1,0},{PORT_015,1,1,0}},0},
   {{"vphaddd", {OP_YMM, OP_MEC, OP_NON, OP_YMM}}, 6, {{PORT_23,7,1,0},{PORT_015,1,1,0},{PORT_015,1,1,0},{PORT_015,1,1,0},{PORT_015,1,1,0},{PORT_015,1,1,0}},0},

/* ==================== VPEXTRQ ==================== */
   {{"vpextrq", {OP_VAL,OP_XMM, OP_NON, OP_REG}}, 2, {{PORT_0,2,1,0},{PORT_5,1,1,0}},0},
   {{"vpextrq", {OP_VAL,OP_XMM, OP_NON, OP_MEM}}, 2, {{PORT_237,1,1,MOP_UNCHAINED},{PORT_4,2,1,0}},0},
   {{"vpextrq", {OP_VAL,OP_XMM, OP_NON, OP_MEC}}, 2, {{PORT_23,1,1,MOP_UNCHAINED},{PORT_4,2,1,0}},0},

/* ==================== VPEXTRACTI128 ==================== */
   {{"vextracti128", {OP_VAL,OP_YMM, OP_NON, OP_XMM}}, 1, {{PORT_5,1,1,0}},0},
   {{"vextracti128", {OP_VAL,OP_YMM, OP_NON, OP_MEM}}, 2, {{PORT_237,1,1,MOP_UNCHAINED},{PORT_4,2,1,0}},0},
   {{"vextracti128", {OP_VAL,OP_YMM, OP_NON, OP_MEC}}, 2, {{PORT_23,1,1,MOP_UNCHAINED},{PORT_4,2,1,0}}}
	};

const int known_icount = sizeof(instruction_set) / sizeof(FInstructionDesc);

FInstructionDesc *inst_idx[sizeof(instruction_set) / sizeof(FInstructionDesc)];

int _compare_inst_def(const FInstructionDef *i1,const FInstructionDef *i2)
   {
   int charres = strncmp (i1->mnem,i2->mnem,sizeof(i1->mnem));
   if (charres)
      return charres;
   uint32_t op1 = *(int *)(i1->operands);
   uint32_t op2 = *(int *)(i2->operands);
   if (op1 < op2) return -1;
   if (op1 > op2) return 1;
   return 0;
   }

int compare_inst_def(const void *a,const void *b)
   {
   FInstructionDef *i1 = *(FInstructionDef **)a;
   FInstructionDef *i2 = *(FInstructionDef **)b;
   return _compare_inst_def(i1,i2);
   }

int MAX_LATENCY = 0;

void parser_init(void)
   {
   int i,j;

   for (i = 0; i < known_icount; i++)
      {
      inst_idx[i] = &instruction_set[i];
      instruction_set[i].latency = 0;
      for (j = 0 ; j < instruction_set[i].mops_cnt; j++)
         {
         if (!(instruction_set[i].ops[j].flags & MOP_UNCHAINED))
            instruction_set[i].latency += instruction_set[i].ops[j].latency;
         }
      if (instruction_set[i].latency > MAX_LATENCY)
         MAX_LATENCY = instruction_set[i].latency;
      }
   qsort(inst_idx,known_icount,sizeof(FInstructionDef *),compare_inst_def);
   }

static int _inst_search(FInstruction *inst)
   {
   int i;
   int low = -1;
   int hi = known_icount;
   int pos = known_icount / 2;
   int res;

   while (res = _compare_inst_def(&inst_idx[pos]->def,&inst->def))
      {
      if (res < 0)
         low = pos;
      else
         hi = pos;
      pos = low + (hi - low) / 2;
      if (pos <= low || pos >= hi)
         return 0;
      }
   inst->mops_cnt = inst_idx[pos]->mops_cnt;
   inst->ops = inst_idx[pos]->ops;
   inst->targ_dep = inst_idx[pos]->targ_dep;
   inst->latency = inst_idx[pos]->latency;
   return 1;
   }

static char *_next_param(char *pos)
   {
   int inbrackets = 0;
   while ((pos[0] != ',' || inbrackets) && pos[0] != '\t' && pos[0] != '\r' && pos[0] != '\n' && pos[0] != '#')
      {
      if (pos[0] == '(')
         inbrackets = 1;
      else if (pos[0] == ')')
         inbrackets = 0;
      pos++;
      }
   char *end = pos;
   while (pos[0] == ' ' || pos[0] == '\t')
      pos++;
   if (pos[0] == ',')
      pos++;
   while (pos[0] == ' ' || pos[0] == '\t')
      pos++;
   int eol = (pos[0] == '\r' || pos[0] == '\n' || pos[0] == '#');
   *end = 0;
   return eol ? NULL : pos;
   }

uint8_t get_reg(char *string, int *reg, int *prevdep)
   {
   *prevdep = 0;
   *reg = REG_NONE;
   switch (string[0])
      {
      case 'd':
         if (string[1] == 'i') return *prevdep = 1,*reg = REG_RDI, OP_REG;
         goto low_regs;
      case 's':
         if (string[1] == 'i') return *prevdep = 1,*reg = REG_RSI, OP_REG;
         if (string[1] == 'p') return *reg = REG_NONE, OP_REG;
         return OP_BAD;
      case 'b': 
         if (string[1] == 'p') return *reg = REG_NONE, OP_REG;
      case 'a':
      case 'c':
         {
low_regs:
         switch (string[1])
            {
            case 'x': case 'h': case 'l':
               return *prevdep = 1,*reg = REG_RAX + string[0] - 'a', OP_REG;
            }
         return OP_BAD;
         }
      case 'e':
         goto hi_regs;

      case 'x':
         {
         if (string[1] != 'm' && string[2] != 'm')
            return OP_BAD;
         int rnum = strtoul(&string[3],NULL,0);
         if (rnum > 15)
            return OP_BAD;
         return *reg = REG_YMM0 + rnum, OP_XMM;
         }
      case 'y':
         {
         if (string[1] != 'm' && string[2] != 'm')
            return OP_BAD;
         int rnum = strtoul(&string[3],NULL,0);
         if (rnum > 15)
            return OP_BAD;
         return *reg = REG_YMM0 + rnum, OP_YMM;
         }
      case 'r':
         {
         int rnum = strtol(&string[1],NULL,0);
         if (!rnum)
            {
hi_regs:
            switch(string[1])
               {
               case 'c':
               case 'a':
                  {
                  if (string[2] == 'x')
                     return *reg = REG_RAX + string[1] - 'a', OP_REG;
                  return OP_BAD;
                  }
               case 'b':
                  {
                  if (string[2] == 'x')
                     return *reg = REG_RBX, OP_REG;
                  if (string[2] == 'p')
                     return *reg = REG_NONE, OP_REG;
                  return OP_BAD;
                  }
               case 'd':
                  {
                  if (string[2] == 'x')
                     return *reg = REG_RDX, OP_REG;
                  if (string[2] == 'i')
                     return *reg = REG_RDI, OP_REG;
                  return OP_BAD;
                  }
               case 's':
                  {
                  if (string[2] == 'i')
                     return *reg = REG_RSI, OP_REG;
                  if (string[2] == 'p')
                     return *reg = REG_NONE, OP_REG;
                  return OP_BAD;
                  }
               case 'i':
                  {
                  if (string[2] == 'p')
                     return *reg = REG_NONE, OP_REG;
                  return OP_BAD;
                  }
               }
            return OP_BAD;
            }
         if (rnum < 8 || rnum > 15)
            return OP_BAD;
         return *reg = REG_R8 -8 + rnum, OP_REG;
         }
      }
   return OP_BAD;
   }

// prevdep - запись в регистр зависит от его предыдущего содержания, он попадает в 
uint8_t get_param_type(char *param,uint64_t *reg_usage, int *prev_dep)
   {
   *prev_dep = 0;
   int has_shift = 0;
   switch (*param)
      {
      case '$': // Константа
         return OP_VAL;
      case '%':
         { // Регистр
         int reg = REG_NONE;
         uint8_t rv = get_reg(&param[1],&reg,prev_dep);
         if (reg != REG_NONE)
            *reg_usage |= 1LL << reg;
         return rv;
         }
      case '.':
         {
         while (param[0] != '(' && param[0] != ',' && param[0] != '\t' && param[0] != '\r' && param[0] != '\n' && param[0] != '#')
            param++;
         if (param[0] == '(')
            {
            has_shift = 1;
            goto bracket;
            }
         return OP_MEM;
         }
      case '-':
      case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9':
         { // Сдвиг
         strtol(param,&param,0);
         if (param[0] != '(')
            return OP_BAD;
         has_shift = 1;
         }
      case '(':
bracket:
         {
         int pd,reg;
         int ccnt = 0;
         char *pos = &param[0];
         do
            {
            pos++;
            if (*pos == '%')
               {
               uint8_t rv = get_reg(pos+1,&reg,&pd);
               if (reg != REG_NONE)
                  *reg_usage |= 1LL << reg;
               }
            ccnt++;
            while (*pos != ')' && *pos != ',')
               pos++;
            }
         while (*pos != ')');

         return (ccnt + has_shift > 2) ?  OP_MEC : OP_MEM;
         }
      }
   return OP_NON;
   }

FInstructionSet *parser_read_file(const char *filename)
	{
	char buf[512];
	FILE *f;
   int i;

	f = fopen(filename,"r");
	if (!f) return NULL;

   FInstructionSet *rv = (FInstructionSet *)malloc(sizeof(FInstructionSet) + sizeof(FInstruction) * INSTS_CNT_STEP);
   int set_cap = INSTS_CNT_STEP;
   rv->inst_cnt = 0;
   memset(rv->reg_initial_usage,0,sizeof(rv->reg_initial_usage));

   FInstruction *work = &rv->instructions[0];
   memset(work,0,sizeof(FInstruction));
		
   int lnum = 1;
   FInstruction *regs_last_usages[REG_MAX] = {0};
   int tick = 0;
   int tick_use_count = 0;

   uint64_t output_regs = 0;

	for (;fgets(buf,512,f); lnum++)
		{
      uint8_t pts[4] = {0};
      uint64_t reg_usages[4] = {0};
      int pts_cnt = 0;
      int regs[REG_MAX] = {0};
      int treg = 0;

      int pcnt = 0;
      char *pos = &buf[0];
      while (pos[0] == ' ' || pos[0] == '\t')  pos++;
		if (pos[0] == '.' || pos[0] == '#')
			continue;
		char *cmd = pos;
      while  (pos[0] != ' ' && pos[0] != '\t' && pos[0] != '\r' && pos[0] != '\n')  pos++;
		*pos++ = 0;
      if (!*cmd)
         continue;
      while (pos[0] == ' ' || pos[0] == '\t') pos++;

      int prev_dep = 0;
      do
         {
         pts[pts_cnt] = get_param_type(pos,&reg_usages[pts_cnt],&prev_dep);
         if (pts[pts_cnt] == OP_BAD)
            {
            printf("%s %d: instruction %s has unknown param format\n",filename,lnum,work->def.mnem);
            }
         if (pts[pts_cnt] == OP_NON)
            break;
         pts_cnt++;
         pos = _next_param(pos);
         }
      while (pts_cnt < 4 && pos);

      uint64_t reg_usage = 0; // Регистры от которых зависит инструкция
      uint64_t targ_regs; // Регистры в аргументе назначения
      strcpy(work->def.mnem,cmd);
      if (pts_cnt)
         {
         work->def.operands[3] = pts[pts_cnt - 1];
         targ_regs = reg_usages[pts_cnt - 1];

         for (i = 0; i < pts_cnt - 1; i++)
            {
            work->def.operands[i] = pts[i];
            reg_usage |= reg_usages[i];
            }
         }

      if (!_inst_search(work))
         {
         printf("%s %d: unknown instruction %s\n",filename,lnum,work->def.mnem);
         return 0;
         }

      if (work->def.operands[3] == OP_REG || work->def.operands[3] == OP_XMM || work->def.operands[3] == OP_YMM)
         {
         work->treg = __builtin_ctz(targ_regs);
         output_regs &= ~reg_usage;
         if (prev_dep || work->targ_dep)
            reg_usage |= targ_regs;
         output_regs |= targ_regs;
         }
      else
         {
         work->treg = REG_NONE;
         reg_usage |= targ_regs;
         output_regs &= ~reg_usage;
         }

      int itick = (tick_use_count >= 3) ? tick + 1 : tick;

      for (i = 0; i < REG_MAX; i++)
         {
         if (!((1LL << i) & reg_usage))
            continue;
         if (regs_last_usages[i] && regs_last_usages[i]->treg == i && regs_last_usages[i]->tick + regs_last_usages[i]->latency > itick)
            itick = regs_last_usages[i]->tick + regs_last_usages[i]->latency;
         }

      work->tick = itick;
      work->line = lnum;
      if (tick != itick)
         tick_use_count = 0;
      else
         tick_use_count++;
      tick = itick;
      
      for (i = 0; i < REG_MAX; i++)
         {
         if (!((1LL << i) & reg_usage))
            continue;
         if (regs_last_usages[i])
            regs_last_usages[i]->reg_next_usage[i] = work->tick;
         else
            rv->reg_initial_usage[i] = work->tick;
         regs_last_usages[i] = work;
         }
      if (work->treg != REG_NONE)
         regs_last_usages[work->treg] = work;

process_command:
      if (work->mops_cnt)
         {
         rv->inst_cnt++;
         if (rv->inst_cnt >= set_cap)
            {
            set_cap += INSTS_CNT_STEP;
            rv = (FInstructionSet *)realloc(rv,sizeof(FInstructionSet) + sizeof(FInstruction) * set_cap);
            work = &rv->instructions[rv->inst_cnt];
            }
         else
            work++;
         memset(work,0,sizeof(FInstruction));
         }
      }

   for (i = 0; i < REG_MAX; i++)
      {
      if (!((1LL << i) & output_regs))
         continue;
      regs_last_usages[i]->reg_next_usage[i] = tick;
      }

   fclose(f);
   rv->inst_cnt = work - rv->instructions;
   return rv;
   }