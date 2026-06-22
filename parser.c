#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "parser.h"

FInstructionDesc instruction_set[] = {
   {{"movabsq", {OP_REG, OP_NON, OP_NON, OP_REG}}, 1, {{PORT_0156,1,1,0}},0},
   {{"movabsq", {OP_VAL, OP_NON, OP_NON, OP_REG}}, 1, {{PORT_0156,1,1,0}},0},
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
   {{"leal", {OP_MEC, OP_NON, OP_NON, OP_REG}}, 1, {{PORT_1,3,1,0}},0},

   {{"leaq", {OP_MEM, OP_NON, OP_NON, OP_REG}}, 1, {{PORT_15,1,1,0}},0},
   {{"leaq", {OP_MEC, OP_NON, OP_NON, OP_REG}}, 1, {{PORT_1,3,1,0}},0},

   {{"addb", {OP_VAL, OP_NON, OP_NON, OP_REG}}, 1, {{PORT_0156,1,1,0}},IF_TARGET_DEP},
   {{"addb", {OP_REG, OP_NON, OP_NON, OP_REG}}, 1, {{PORT_0156,1,1,0}},IF_TARGET_DEP},
   {{"addb", {OP_MEM, OP_NON, OP_NON, OP_REG}}, 2, {{PORT_23,4,1,0},{PORT_0156,1,1,0}},IF_TARGET_DEP},
   {{"addb", {OP_MEC, OP_NON, OP_NON, OP_REG}}, 2, {{PORT_23,5,1,0},{PORT_0156,1,1,0}},IF_TARGET_DEP},
   {{"addb", {OP_REG, OP_NON, OP_NON, OP_MEM}}, 4, {{PORT_23,4,1,0},{PORT_0156,1,1,0},{PORT_237,1,1,MOP_UNCHAINED},{PORT_4,2,1,0}},IF_TARGET_DEP},
   {{"addb", {OP_REG, OP_NON, OP_NON, OP_MEC}}, 4, {{PORT_23,5,1,0},{PORT_0156,1,1,0},{PORT_23,1,1,MOP_UNCHAINED},{PORT_4,2,1,0}},IF_TARGET_DEP},

   {{"addw", {OP_REG, OP_NON, OP_NON, OP_REG}}, 1, {{PORT_0156,1,1,0}},IF_TARGET_DEP},
   {{"addw", {OP_MEM, OP_NON, OP_NON, OP_REG}}, 2, {{PORT_23,4,1,0},{PORT_0156,1,1,0}},IF_TARGET_DEP},
   {{"addw", {OP_MEC, OP_NON, OP_NON, OP_REG}}, 2, {{PORT_23,5,1,0},{PORT_0156,1,1,0}},IF_TARGET_DEP},
   {{"addw", {OP_REG, OP_NON, OP_NON, OP_MEM}}, 4, {{PORT_23,4,1,0},{PORT_0156,1,1,0},{PORT_237,1,1,MOP_UNCHAINED},{PORT_4,2,1,0}},IF_TARGET_DEP},
   {{"addw", {OP_REG, OP_NON, OP_NON, OP_MEC}}, 4, {{PORT_23,5,1,0},{PORT_0156,1,1,0},{PORT_23,1,1,MOP_UNCHAINED},{PORT_4,2,1,0}},IF_TARGET_DEP},

   {{"addl", {OP_VAL, OP_NON, OP_NON, OP_REG}}, 1, {{PORT_0156,1,1,0}},IF_TARGET_DEP},
   {{"addl", {OP_REG, OP_NON, OP_NON, OP_REG}}, 1, {{PORT_0156,1,1,0}},IF_TARGET_DEP},
   {{"addl", {OP_MEM, OP_NON, OP_NON, OP_REG}}, 2, {{PORT_23,4,1,0},{PORT_0156,1,1,0}},IF_TARGET_DEP},
   {{"addl", {OP_MEC, OP_NON, OP_NON, OP_REG}}, 2, {{PORT_23,5,1,0},{PORT_0156,1,1,0}},IF_TARGET_DEP},
   {{"addl", {OP_REG, OP_NON, OP_NON, OP_MEM}}, 4, {{PORT_23,4,1,0},{PORT_0156,1,1,0},{PORT_237,1,1,MOP_UNCHAINED},{PORT_4,2,1,0}},IF_TARGET_DEP},
   {{"addl", {OP_REG, OP_NON, OP_NON, OP_MEC}}, 4, {{PORT_23,5,1,0},{PORT_0156,1,1,0},{PORT_23,1,1,MOP_UNCHAINED},{PORT_4,2,1,0}},IF_TARGET_DEP},

   {{"addq", {OP_VAL, OP_NON, OP_NON, OP_REG}}, 1, {{PORT_0156,1,1,0}},IF_TARGET_DEP},
   {{"addq", {OP_REG, OP_NON, OP_NON, OP_REG}}, 1, {{PORT_0156,1,1,0}},IF_TARGET_DEP},
   {{"addq", {OP_MEM, OP_NON, OP_NON, OP_REG}}, 2, {{PORT_23,4,1,0},{PORT_0156,1,1,0}},IF_TARGET_DEP},
   {{"addq", {OP_MEC, OP_NON, OP_NON, OP_REG}}, 2, {{PORT_23,5,1,0},{PORT_0156,1,1,0}},IF_TARGET_DEP},
   {{"addq", {OP_REG, OP_NON, OP_NON, OP_MEM}}, 4, {{PORT_23,4,1,0},{PORT_0156,1,1,0},{PORT_237,1,1,MOP_UNCHAINED},{PORT_4,2,1,0}},IF_TARGET_DEP},
   {{"addq", {OP_REG, OP_NON, OP_NON, OP_MEC}}, 4, {{PORT_23,5,1,0},{PORT_0156,1,1,0},{PORT_23,1,1,MOP_UNCHAINED},{PORT_4,2,1,0}},IF_TARGET_DEP},

   {{"subb", {OP_REG, OP_NON, OP_NON, OP_REG}}, 1, {{PORT_0156,1,1,0}},IF_TARGET_DEP},
   {{"subb", {OP_MEM, OP_NON, OP_NON, OP_REG}}, 2, {{PORT_23,4,1,0},{PORT_0156,1,1,0}},IF_TARGET_DEP},
   {{"subb", {OP_MEC, OP_NON, OP_NON, OP_REG}}, 2, {{PORT_23,5,1,0},{PORT_0156,1,1,0}},IF_TARGET_DEP},
   {{"subb", {OP_REG, OP_NON, OP_NON, OP_MEM}}, 4, {{PORT_23,4,1,0},{PORT_0156,1,1,0},{PORT_237,1,1,MOP_UNCHAINED},{PORT_4,2,1,0}},IF_TARGET_DEP},
   {{"subb", {OP_REG, OP_NON, OP_NON, OP_MEC}}, 4, {{PORT_23,5,1,0},{PORT_0156,1,1,0},{PORT_23,1,1,MOP_UNCHAINED},{PORT_4,2,1,0}},IF_TARGET_DEP},

   {{"subw", {OP_REG, OP_NON, OP_NON, OP_REG}}, 1, {{PORT_0156,1,1,0}},IF_TARGET_DEP},
   {{"subw", {OP_MEM, OP_NON, OP_NON, OP_REG}}, 2, {{PORT_23,4,1,0},{PORT_0156,1,1,0}},IF_TARGET_DEP},
   {{"subw", {OP_MEC, OP_NON, OP_NON, OP_REG}}, 2, {{PORT_23,5,1,0},{PORT_0156,1,1,0}},IF_TARGET_DEP},
   {{"subw", {OP_REG, OP_NON, OP_NON, OP_MEM}}, 4, {{PORT_23,4,1,0},{PORT_0156,1,1,0},{PORT_237,1,1,MOP_UNCHAINED},{PORT_4,2,1,0}},IF_TARGET_DEP},
   {{"subw", {OP_REG, OP_NON, OP_NON, OP_MEC}}, 4, {{PORT_23,5,1,0},{PORT_0156,1,1,0},{PORT_23,1,1,MOP_UNCHAINED},{PORT_4,2,1,0}},IF_TARGET_DEP},

   {{"subl", {OP_VAL, OP_NON, OP_NON, OP_REG}}, 1, {{PORT_0156,1,1,0}},IF_TARGET_DEP},
   {{"subl", {OP_REG, OP_NON, OP_NON, OP_REG}}, 1, {{PORT_0156,1,1,0}},IF_TARGET_DEP},
   {{"subl", {OP_MEM, OP_NON, OP_NON, OP_REG}}, 2, {{PORT_23,4,1,0},{PORT_0156,1,1,0}},IF_TARGET_DEP},
   {{"subl", {OP_MEC, OP_NON, OP_NON, OP_REG}}, 2, {{PORT_23,5,1,0},{PORT_0156,1,1,0}},IF_TARGET_DEP},
   {{"subl", {OP_REG, OP_NON, OP_NON, OP_MEM}}, 4, {{PORT_23,4,1,0},{PORT_0156,1,1,0},{PORT_237,1,1,MOP_UNCHAINED},{PORT_4,2,1,0}},IF_TARGET_DEP},
   {{"subl", {OP_REG, OP_NON, OP_NON, OP_MEC}}, 4, {{PORT_23,5,1,0},{PORT_0156,1,1,0},{PORT_23,1,1,MOP_UNCHAINED},{PORT_4,2,1,0}},IF_TARGET_DEP},

   {{"subq", {OP_VAL, OP_NON, OP_NON, OP_REG}}, 1, {{PORT_0156,1,1,0}},IF_TARGET_DEP},
   {{"subq", {OP_REG, OP_NON, OP_NON, OP_REG}}, 1, {{PORT_0156,1,1,0}},IF_TARGET_DEP},
   {{"subq", {OP_MEM, OP_NON, OP_NON, OP_REG}}, 2, {{PORT_23,4,1,0},{PORT_0156,1,1,0}},IF_TARGET_DEP},
   {{"subq", {OP_MEC, OP_NON, OP_NON, OP_REG}}, 2, {{PORT_23,5,1,0},{PORT_0156,1,1,0}},IF_TARGET_DEP},
   {{"subq", {OP_REG, OP_NON, OP_NON, OP_MEM}}, 4, {{PORT_23,4,1,0},{PORT_0156,1,1,0},{PORT_237,1,1,MOP_UNCHAINED},{PORT_4,2,1,0}},IF_TARGET_DEP},
   {{"subq", {OP_REG, OP_NON, OP_NON, OP_MEC}}, 4, {{PORT_23,5,1,0},{PORT_0156,1,1,0},{PORT_23,1,1,MOP_UNCHAINED},{PORT_4,2,1,0}},IF_TARGET_DEP},

   {{"andl", {OP_VAL, OP_NON, OP_NON, OP_REG}}, 1, {{PORT_0156,1,1,0}},IF_TARGET_DEP},
   {{"andl", {OP_REG, OP_NON, OP_NON, OP_REG}}, 1, {{PORT_0156,1,1,0}},IF_TARGET_DEP},
   {{"andl", {OP_MEM, OP_NON, OP_NON, OP_REG}}, 2, {{PORT_23,4,1,0},{PORT_0156,1,1,0}},IF_TARGET_DEP},
   {{"andl", {OP_MEC, OP_NON, OP_NON, OP_REG}}, 2, {{PORT_23,5,1,0},{PORT_0156,1,1,0}},IF_TARGET_DEP},
   {{"andl", {OP_REG, OP_NON, OP_NON, OP_MEM}}, 4, {{PORT_23,4,1,0},{PORT_0156,1,1,0},{PORT_237,1,1,MOP_UNCHAINED},{PORT_4,2,1,0}},IF_TARGET_DEP},
   {{"andl", {OP_REG, OP_NON, OP_NON, OP_MEC}}, 4, {{PORT_23,5,1,0},{PORT_0156,1,1,0},{PORT_23,1,1,MOP_UNCHAINED},{PORT_4,2,1,0}},IF_TARGET_DEP},

   {{"andq", {OP_VAL, OP_NON, OP_NON, OP_REG}}, 1, {{PORT_0156,1,1,0}},IF_TARGET_DEP},
   {{"andq", {OP_REG, OP_NON, OP_NON, OP_REG}}, 1, {{PORT_0156,1,1,0}},IF_TARGET_DEP},
   {{"andq", {OP_MEM, OP_NON, OP_NON, OP_REG}}, 2, {{PORT_23,4,1,0},{PORT_0156,1,1,0}},IF_TARGET_DEP},
   {{"andq", {OP_MEC, OP_NON, OP_NON, OP_REG}}, 2, {{PORT_23,5,1,0},{PORT_0156,1,1,0}},IF_TARGET_DEP},
   {{"andq", {OP_REG, OP_NON, OP_NON, OP_MEM}}, 4, {{PORT_23,4,1,0},{PORT_0156,1,1,0},{PORT_237,1,1,MOP_UNCHAINED},{PORT_4,2,1,0}},IF_TARGET_DEP},
   {{"andq", {OP_REG, OP_NON, OP_NON, OP_MEC}}, 4, {{PORT_23,5,1,0},{PORT_0156,1,1,0},{PORT_23,1,1,MOP_UNCHAINED},{PORT_4,2,1,0}},IF_TARGET_DEP},

   {{"xorl", {OP_VAL, OP_NON, OP_NON, OP_REG}}, 1, {{PORT_0156,1,1,0}},IF_TARGET_DEP},
   {{"xorl", {OP_REG, OP_NON, OP_NON, OP_REG}}, 1, {{PORT_0156,1,1,0}},IF_TARGET_DEP},
   {{"xorl", {OP_MEM, OP_NON, OP_NON, OP_REG}}, 2, {{PORT_23,4,1,0},{PORT_0156,1,1,0}},IF_TARGET_DEP},
   {{"xorl", {OP_MEC, OP_NON, OP_NON, OP_REG}}, 2, {{PORT_23,5,1,0},{PORT_0156,1,1,0}},IF_TARGET_DEP},
   {{"xorl", {OP_REG, OP_NON, OP_NON, OP_MEM}}, 4, {{PORT_23,4,1,0},{PORT_0156,1,1,0},{PORT_237,1,1,MOP_UNCHAINED},{PORT_4,2,1,0}},IF_TARGET_DEP},
   {{"xorl", {OP_REG, OP_NON, OP_NON, OP_MEC}}, 4, {{PORT_23,5,1,0},{PORT_0156,1,1,0},{PORT_23,1,1,MOP_UNCHAINED},{PORT_4,2,1,0}},IF_TARGET_DEP},

   {{"xorq", {OP_VAL, OP_NON, OP_NON, OP_REG}}, 1, {{PORT_0156,1,1,0}},IF_TARGET_DEP},
   {{"xorq", {OP_REG, OP_NON, OP_NON, OP_REG}}, 1, {{PORT_0156,1,1,0}},IF_TARGET_DEP},
   {{"xorq", {OP_MEM, OP_NON, OP_NON, OP_REG}}, 2, {{PORT_23,4,1,0},{PORT_0156,1,1,0}},IF_TARGET_DEP},
   {{"xorq", {OP_MEC, OP_NON, OP_NON, OP_REG}}, 2, {{PORT_23,5,1,0},{PORT_0156,1,1,0}},IF_TARGET_DEP},
   {{"xorq", {OP_REG, OP_NON, OP_NON, OP_MEM}}, 4, {{PORT_23,4,1,0},{PORT_0156,1,1,0},{PORT_237,1,1,MOP_UNCHAINED},{PORT_4,2,1,0}},IF_TARGET_DEP},
   {{"xorq", {OP_REG, OP_NON, OP_NON, OP_MEC}}, 4, {{PORT_23,5,1,0},{PORT_0156,1,1,0},{PORT_23,1,1,MOP_UNCHAINED},{PORT_4,2,1,0}},IF_TARGET_DEP},

   {{"orl", {OP_VAL, OP_NON, OP_NON, OP_REG}}, 1, {{PORT_0156,1,1,0}},IF_TARGET_DEP},
   {{"orl", {OP_REG, OP_NON, OP_NON, OP_REG}}, 1, {{PORT_0156,1,1,0}},IF_TARGET_DEP},
   {{"orl", {OP_MEM, OP_NON, OP_NON, OP_REG}}, 2, {{PORT_23,4,1,0},{PORT_0156,1,1,0}},IF_TARGET_DEP},
   {{"orl", {OP_MEC, OP_NON, OP_NON, OP_REG}}, 2, {{PORT_23,5,1,0},{PORT_0156,1,1,0}},IF_TARGET_DEP},
   {{"orl", {OP_REG, OP_NON, OP_NON, OP_MEM}}, 4, {{PORT_23,4,1,0},{PORT_0156,1,1,0},{PORT_237,1,1,MOP_UNCHAINED},{PORT_4,2,1,0}},IF_TARGET_DEP},
   {{"orl", {OP_REG, OP_NON, OP_NON, OP_MEC}}, 4, {{PORT_23,5,1,0},{PORT_0156,1,1,0},{PORT_23,1,1,MOP_UNCHAINED},{PORT_4,2,1,0}},IF_TARGET_DEP},

   {{"orq", {OP_VAL, OP_NON, OP_NON, OP_REG}}, 1, {{PORT_0156,1,1,0}},IF_TARGET_DEP},
   {{"orq", {OP_REG, OP_NON, OP_NON, OP_REG}}, 1, {{PORT_0156,1,1,0}},IF_TARGET_DEP},
   {{"orq", {OP_MEM, OP_NON, OP_NON, OP_REG}}, 2, {{PORT_23,4,1,0},{PORT_0156,1,1,0}},IF_TARGET_DEP},
   {{"orq", {OP_MEC, OP_NON, OP_NON, OP_REG}}, 2, {{PORT_23,5,1,0},{PORT_0156,1,1,0}},IF_TARGET_DEP},
   {{"orq", {OP_REG, OP_NON, OP_NON, OP_MEM}}, 4, {{PORT_23,4,1,0},{PORT_0156,1,1,0},{PORT_237,1,1,MOP_UNCHAINED},{PORT_4,2,1,0}},IF_TARGET_DEP},
   {{"orq", {OP_REG, OP_NON, OP_NON, OP_MEC}}, 4, {{PORT_23,5,1,0},{PORT_0156,1,1,0},{PORT_23,1,1,MOP_UNCHAINED},{PORT_4,2,1,0}},IF_TARGET_DEP},

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
   {{"vpblendvb", {OP_XMM, OP_XMM, OP_XMM, OP_XMM}}, 1, {{PORT_015,1,2,0}},0},
   {{"vpblendvb", {OP_XMM, OP_MEM, OP_XMM, OP_XMM}}, 2, {{PORT_23,6,1,0},{PORT_015,1,2,0}},0},
   {{"vpblendvb", {OP_XMM, OP_MEC, OP_XMM, OP_XMM}}, 2, {{PORT_23,6,1,0},{PORT_015,1,2,0}},0},
    /* 256-битные версии (YMM) */
   {{"vpblendvb", {OP_YMM, OP_YMM, OP_YMM, OP_YMM}}, 1, {{PORT_015,1,2,0}},0},
   {{"vpblendvb", {OP_YMM, OP_MEM, OP_YMM, OP_YMM}}, 2, {{PORT_23,7,1,0},{PORT_015,1,2,0}},0},
   {{"vpblendvb", {OP_YMM, OP_MEC, OP_YMM, OP_YMM}}, 2, {{PORT_23,7,1,0},{PORT_015,1,2,0}},0},

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
   {{"vpor", {OP_MEM, OP_XMM, OP_NON, OP_XMM}}, 2, {{PORT_23,6,1,0},{PORT_015,1,1,0}},0},
   {{"vpor", {OP_MEC, OP_XMM, OP_NON, OP_XMM}}, 2, {{PORT_23,6,1,0},{PORT_015,1,1,0}},0},
/* 256-битные версии (YMM) */
   {{"vpor", {OP_YMM, OP_YMM, OP_NON, OP_YMM}}, 1, {{PORT_015,1,1,0}},0},
   {{"vpor", {OP_MEM, OP_YMM, OP_NON, OP_YMM}}, 2, {{PORT_23,7,1,0},{PORT_015,1,1,0}},0},
   {{"vpor", {OP_MEC, OP_YMM, OP_NON, OP_YMM}}, 2, {{PORT_23,7,1,0},{PORT_015,1,1,0}},0},

/* ==================== VPXOR ==================== */
/* 128-битные версии (XMM) */
   {{"vpxor", {OP_XMM, OP_XMM, OP_NON, OP_XMM}}, 1, {{PORT_015,1,1,0}},0},
   {{"vpxor", {OP_MEM, OP_XMM, OP_NON, OP_XMM}}, 2, {{PORT_23,6,1,0},{PORT_015,1,1,0}},0},
   {{"vpxor", {OP_MEC, OP_XMM, OP_NON, OP_XMM}}, 2, {{PORT_23,6,1,0},{PORT_015,1,1,0}},0},
/* 256-битные версии (YMM) */
   {{"vpxor", {OP_YMM, OP_YMM, OP_NON, OP_YMM}}, 1, {{PORT_015,1,1,0}},0},
   {{"vpxor", {OP_MEM, OP_YMM, OP_NON, OP_YMM}}, 2, {{PORT_23,7,1,0},{PORT_015,1,1,0}},0},
   {{"vpxor", {OP_MEC, OP_YMM, OP_NON, OP_YMM}}, 2, {{PORT_23,7,1,0},{PORT_015,1,1,0}},0},

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
   {{"vpsrld", {OP_VAL, OP_XMM, OP_NON, OP_XMM}}, 1, {{PORT_01,1,1,0}},0},
   {{"vpsrld", {OP_VAL, OP_MEM, OP_NON, OP_XMM}}, 2, {{PORT_23,6,1,0},{PORT_01,1,1,0}},0},
   {{"vpsrld", {OP_VAL, OP_MEC, OP_NON, OP_XMM}}, 2, {{PORT_23,6,1,0},{PORT_01,1,1,0}},0},
/* 256-битные версии (YMM) */
   {{"vpsrld", {OP_VAL, OP_YMM, OP_NON, OP_YMM}}, 1, {{PORT_01,1,1,0}},0},
   {{"vpsrld", {OP_VAL, OP_MEM, OP_NON, OP_YMM}}, 2, {{PORT_23,7,1,0},{PORT_01,1,1,0}},0},
   {{"vpsrld", {OP_VAL, OP_MEC, OP_NON, OP_YMM}}, 2, {{PORT_23,7,1,0},{PORT_01,1,1,0}},0},

/* ==================== VPMULLD ==================== */
/* 128-битные версии (XMM) */
   {{"vpmulld", {OP_XMM, OP_XMM, OP_NON, OP_XMM}}, 2, {{PORT_01,5,1,0},{PORT_01,5,1,0}},0},
   {{"vpmulld", {OP_MEM, OP_XMM, OP_NON, OP_XMM}}, 3, {{PORT_23,6,1,0},{PORT_01,5,1,0},{PORT_01,5,1,0}},0},
   {{"vpmulld", {OP_MEC, OP_XMM, OP_NON, OP_XMM}}, 3, {{PORT_23,6,1,0},{PORT_01,5,1,0},{PORT_01,5,1,0}},0},
/* 256-битные версии (YMM) */
   {{"vpmulld", {OP_YMM, OP_YMM, OP_NON, OP_YMM}}, 3, {{PORT_01,4,1,0},{PORT_01,3,1,0},{PORT_01,3,1,0}},0},
   {{"vpmulld", {OP_MEM, OP_YMM, OP_NON, OP_YMM}}, 4, {{PORT_23,7,1,0},{PORT_01,4,1,0},{PORT_01,3,1,0},{PORT_01,3,1,0}},0},
   {{"vpmulld", {OP_MEC, OP_YMM, OP_NON, OP_YMM}}, 4, {{PORT_23,7,1,0},{PORT_01,4,1,0},{PORT_01,3,1,0},{PORT_01,3,1,0}},0},

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
   {{"vpcmpeqd", {OP_MEM, OP_XMM, OP_NON, OP_XMM}}, 2, {{PORT_23,6,1,0},{PORT_015,1,1,0}},0},
   {{"vpcmpeqd", {OP_MEC, OP_XMM, OP_NON, OP_XMM}}, 2, {{PORT_23,6,1,0},{PORT_015,1,1,0}},0},
/* 256-битные версии (YMM) */
   {{"vpcmpeqd", {OP_YMM, OP_YMM, OP_NON, OP_YMM}}, 1, {{PORT_015,1,1,0}},0},
   {{"vpcmpeqd", {OP_MEM, OP_YMM, OP_NON, OP_YMM}}, 2, {{PORT_23,7,1,0},{PORT_015,1,1,0}},0},
   {{"vpcmpeqd", {OP_MEC, OP_YMM, OP_NON, OP_YMM}}, 2, {{PORT_23,7,1,0},{PORT_015,1,1,0}},0},

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

/* ==================== VPMOVMSKB ==================== */
/* 128-битные версии (XMM) */
   {{"vpmovmskb", {OP_XMM, OP_NON, OP_NON, OP_REG}}, 1, {{PORT_0,3,1,0}},0},
/* 256-битные версии (YMM) */
   {{"vpmovmskb", {OP_YMM, OP_NON, OP_NON, OP_REG}}, 1, {{PORT_0,3,1,0}},0},



/* ==================== PDEP ==================== */
   {{"pdep", {OP_REG, OP_REG, OP_NON, OP_REG}}, 1, {{PORT_1,3,1,0}},0},
   {{"pdep", {OP_REG, OP_MEM, OP_NON, OP_REG}}, 2, {{PORT_23,4,1,0},{PORT_1,3,1,0}},0},
   {{"pdep", {OP_REG, OP_MEC, OP_NON, OP_REG}}, 2, {{PORT_23,4,1,0},{PORT_1,3,1,0}},0},

/* ==================== PEXT ==================== */
   {{"pext", {OP_REG, OP_REG, OP_NON, OP_REG}}, 1, {{PORT_1,3,1,0}},0},
   {{"pext", {OP_REG, OP_MEM, OP_NON, OP_REG}}, 2, {{PORT_23,4,1,0},{PORT_1,3,1,0}},0},
   {{"pext", {OP_REG, OP_MEC, OP_NON, OP_REG}}, 2, {{PORT_23,4,1,0},{PORT_1,3,1,0}},0},

/* ==================== POPCNT ==================== */
   {{"popcntl", {OP_REG, OP_NON, OP_NON, OP_REG}}, 1, {{PORT_1,3,1,0}},0},
   {{"popcntl", {OP_MEM, OP_NON, OP_NON, OP_REG}}, 2, {{PORT_23,4,1,0},{PORT_1,3,1,0}},0},
   {{"popcntl", {OP_MEC, OP_NON, OP_NON, OP_REG}}, 2, {{PORT_23,4,1,0},{PORT_1,3,1,0}},0},

/* ==================== CLTQ ==================== */
   {{"cltq", {OP_NON, OP_NON, OP_NON, OP_NON}}, 1, {{PORT_0156,1,1,0}},0},

/* ==================== CMPL ==================== */
   {{"cmpl", {OP_REG, OP_NON, OP_NON, OP_REG}}, 1, {{PORT_0156,1,1,0}},IF_NO_TARGET},
   {{"cmpl", {OP_VAL, OP_NON, OP_NON, OP_REG}}, 1, {{PORT_0156,1,1,0}},IF_NO_TARGET},

/* ==================== TESTL ==================== */
   {{"testl", {OP_REG, OP_NON, OP_NON, OP_REG}}, 1, {{PORT_0156,1,1,0}},IF_NO_TARGET},
   {{"testl", {OP_VAL, OP_NON, OP_NON, OP_REG}}, 1, {{PORT_0156,1,1,0}},IF_NO_TARGET},

/* ==================== SARL ==================== */
   {{"sarl", {OP_VAL, OP_NON, OP_NON, OP_REG}}, 1, {{PORT_06,1,1,0}},IF_TARGET_DEP},
   {{"sarl", {OP_VAL, OP_NON, OP_NON, OP_MEM}}, 4, {{PORT_23,4,1,0},{PORT_06,1,1,0},{PORT_237,1,1,MOP_UNCHAINED},{PORT_4,2,1,0}},IF_TARGET_DEP},
   {{"sarl", {OP_VAL, OP_NON, OP_NON, OP_MEC}}, 4, {{PORT_23,4,1,0},{PORT_06,1,1,0},{PORT_23,1,1,MOP_UNCHAINED},{PORT_4,2,1,0}},IF_TARGET_DEP},

/* ==================== SALL ==================== */
   {{"sall", {OP_VAL, OP_NON, OP_NON, OP_REG}}, 1, {{PORT_06,1,1,0}},IF_TARGET_DEP},
   {{"sall", {OP_VAL, OP_NON, OP_NON, OP_MEM}}, 4, {{PORT_23,4,1,0},{PORT_06,1,1,0},{PORT_237,1,1,MOP_UNCHAINED},{PORT_4,2,1,0}},IF_TARGET_DEP},
   {{"sall", {OP_VAL, OP_NON, OP_NON, OP_MEC}}, 4, {{PORT_23,4,1,0},{PORT_06,1,1,0},{PORT_23,1,1,MOP_UNCHAINED},{PORT_4,2,1,0}},IF_TARGET_DEP},

/* ==================== SALQ ==================== */
   {{"salq", {OP_VAL, OP_NON, OP_NON, OP_REG}}, 1, {{PORT_06,1,1,0}},IF_TARGET_DEP},
   {{"salq", {OP_VAL, OP_NON, OP_NON, OP_MEM}}, 4, {{PORT_23,4,1,0},{PORT_06,1,1,0},{PORT_237,1,1,MOP_UNCHAINED},{PORT_4,2,1,0}},IF_TARGET_DEP},
   {{"salq", {OP_VAL, OP_NON, OP_NON, OP_MEC}}, 4, {{PORT_23,4,1,0},{PORT_06,1,1,0},{PORT_23,1,1,MOP_UNCHAINED},{PORT_4,2,1,0}},IF_TARGET_DEP},

/* ==================== SARQ ==================== */
   {{"sarq", {OP_VAL, OP_NON, OP_NON, OP_REG}}, 1, {{PORT_06,1,1,0}},IF_TARGET_DEP},
   {{"sarq", {OP_VAL, OP_NON, OP_NON, OP_MEM}}, 4, {{PORT_23,4,1,0},{PORT_06,1,1,0},{PORT_237,1,1,MOP_UNCHAINED},{PORT_4,2,1,0}},IF_TARGET_DEP},
   {{"sarq", {OP_VAL, OP_NON, OP_NON, OP_MEC}}, 4, {{PORT_23,4,1,0},{PORT_06,1,1,0},{PORT_23,1,1,MOP_UNCHAINED},{PORT_4,2,1,0}},IF_TARGET_DEP},

/* ==================== SHRL ==================== */
   {{"shrl", {OP_VAL, OP_NON, OP_NON, OP_REG}}, 1, {{PORT_06,1,1,0}},IF_TARGET_DEP},
   {{"shrl", {OP_VAL, OP_NON, OP_NON, OP_MEM}}, 4, {{PORT_23,4,1,0},{PORT_06,1,1,0},{PORT_237,1,1,MOP_UNCHAINED},{PORT_4,2,1,0}},IF_TARGET_DEP},
   {{"shrl", {OP_VAL, OP_NON, OP_NON, OP_MEC}}, 4, {{PORT_23,4,1,0},{PORT_06,1,1,0},{PORT_23,1,1,MOP_UNCHAINED},{PORT_4,2,1,0}},IF_TARGET_DEP},

/* ==================== SHRQ ==================== */
   {{"shrq", {OP_VAL, OP_NON, OP_NON, OP_REG}}, 1, {{PORT_06,1,1,0}},IF_TARGET_DEP},
   {{"shrq", {OP_VAL, OP_NON, OP_NON, OP_MEM}}, 4, {{PORT_23,4,1,0},{PORT_06,1,1,0},{PORT_237,1,1,MOP_UNCHAINED},{PORT_4,2,1,0}},IF_TARGET_DEP},
   {{"shrq", {OP_VAL, OP_NON, OP_NON, OP_MEC}}, 4, {{PORT_23,4,1,0},{PORT_06,1,1,0},{PORT_23,1,1,MOP_UNCHAINED},{PORT_4,2,1,0}},IF_TARGET_DEP},

/* ==================== INCL ==================== */
   {{"incl", {OP_NON, OP_NON, OP_NON, OP_REG}}, 1, {{PORT_0156,1,1,0}},IF_TARGET_DEP},
   {{"incl", {OP_NON, OP_NON, OP_NON, OP_MEM}}, 4, {{PORT_23,4,1,0},{PORT_0156,1,1,0},{PORT_237,1,1,MOP_UNCHAINED},{PORT_4,2,1,0}},IF_TARGET_DEP},
   {{"incl", {OP_NON, OP_NON, OP_NON, OP_MEC}}, 4, {{PORT_23,4,1,0},{PORT_0156,1,1,0},{PORT_23,1,1,MOP_UNCHAINED},{PORT_4,2,1,0}},IF_TARGET_DEP},

/* ==================== INCQ ==================== */
   {{"incq", {OP_NON, OP_NON, OP_NON, OP_REG}}, 1, {{PORT_0156,1,1,0}},IF_TARGET_DEP},
   {{"incq", {OP_NON, OP_NON, OP_NON, OP_MEM}}, 4, {{PORT_23,4,1,0},{PORT_0156,1,1,0},{PORT_237,1,1,MOP_UNCHAINED},{PORT_4,2,1,0}},IF_TARGET_DEP},
   {{"incq", {OP_NON, OP_NON, OP_NON, OP_MEC}}, 4, {{PORT_23,4,1,0},{PORT_0156,1,1,0},{PORT_23,1,1,MOP_UNCHAINED},{PORT_4,2,1,0}},IF_TARGET_DEP},

/* ==================== CMOVA ==================== */
   {{"cmova", {OP_REG, OP_NON, OP_NON, OP_REG}}, 2, {{PORT_0156,2,2,0}},IF_TARGET_DEP},
   {{"cmova", {OP_MEM, OP_NON, OP_NON, OP_REG}}, 3, {{PORT_23,4,1,0},{PORT_0156,2,2,0}},IF_TARGET_DEP},
   {{"cmova", {OP_MEC, OP_NON, OP_NON, OP_REG}}, 3, {{PORT_23,4,1,0},{PORT_0156,2,2,0}},IF_TARGET_DEP},

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
   {{"vfmadd231ps", {OP_YMM, OP_YMM, OP_NON, OP_YMM}}, 1, {{PORT_01,4,1,0}},IF_TARGET_DEP},

/* ==================== VUNPCKLPS ==================== */
/* 128-битные версии (XMM) */
   {{"vunpcklps", {OP_XMM, OP_XMM, OP_NON, OP_XMM}}, 1, {{PORT_5,1,1,0}},IF_TARGET_DEP},
/* 256-битные версии (YMM) */
   {{"vunpcklps", {OP_YMM, OP_YMM, OP_NON, OP_YMM}}, 1, {{PORT_5,1,1,0}},IF_TARGET_DEP},

/* ==================== VUNPCKHPS ==================== */
/* 128-битные версии (XMM) */
   {{"vunpckhps", {OP_XMM, OP_XMM, OP_NON, OP_XMM}}, 1, {{PORT_5,1,1,0}},IF_TARGET_DEP},
/* 256-битные версии (YMM) */
   {{"vunpckhps", {OP_YMM, OP_YMM, OP_NON, OP_YMM}}, 1, {{PORT_5,1,1,0}},IF_TARGET_DEP},

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
   {{"vpcmpeqb", {OP_MEM, OP_XMM, OP_NON, OP_XMM}}, 2, {{PORT_23,6,1,0},{PORT_015,1,1,0}},0},
   {{"vpcmpeqb", {OP_MEC, OP_XMM, OP_NON, OP_XMM}}, 2, {{PORT_23,6,1,0},{PORT_015,1,1,0}},0},

/* 256-битные версии (YMM) */
   {{"vpcmpeqb", {OP_YMM, OP_YMM, OP_NON, OP_YMM}}, 1, {{PORT_015,1,1,0}},0},
   {{"vpcmpeqb", {OP_YMM, OP_MEM, OP_NON, OP_YMM}}, 2, {{PORT_23,7,1,0},{PORT_015,1,1,0}},0},
   {{"vpcmpeqb", {OP_YMM, OP_MEC, OP_NON, OP_YMM}}, 2, {{PORT_23,7,1,0},{PORT_015,1,1,0}},0},
   {{"vpcmpeqb", {OP_MEM, OP_YMM, OP_NON, OP_YMM}}, 2, {{PORT_23,7,1,0},{PORT_015,1,1,0}},0},
   {{"vpcmpeqb", {OP_MEC, OP_YMM, OP_NON, OP_YMM}}, 2, {{PORT_23,7,1,0},{PORT_015,1,1,0}},0},

/* ==================== NOTL ==================== */
   {{"notl", {OP_NON, OP_NON, OP_NON, OP_REG}}, 1, {{PORT_0156,1,1,0}},IF_TARGET_DEP},
   {{"notl", {OP_NON, OP_NON, OP_NON, OP_MEM}}, 4, {{PORT_23,4,1,0},{PORT_0156,1,1,0},{PORT_237,1,1,MOP_UNCHAINED},{PORT_4,2,1,0}},IF_TARGET_DEP},
   {{"notl", {OP_NON, OP_NON, OP_NON, OP_MEC}}, 4, {{PORT_23,4,1,0},{PORT_0156,1,1,0},{PORT_23,1,1,MOP_UNCHAINED},{PORT_4,2,1,0}},IF_TARGET_DEP},

/* ==================== PREFETCHT2 ==================== */
   {{"prefetcht2", {OP_NON, OP_NON, OP_NON, OP_MEM}}, 1, {{PORT_23,0,1,0}},IF_TARGET_DEP},
   {{"prefetcht2", {OP_NON, OP_NON, OP_NON, OP_MEC}}, 1, {{PORT_23,0,1,0}},IF_TARGET_DEP},
	
/* ==================== VPERMQ ==================== */
   {{"vpermq", {OP_VAL, OP_YMM, OP_NON, OP_YMM}}, 1, {{PORT_5,3,1,0}},0},
   {{"vpermq", {OP_YMM, OP_VAL, OP_NON, OP_YMM}}, 1, {{PORT_5,3,1,0}},0},
   {{"vpermq", {OP_VAL, OP_MEM, OP_NON, OP_YMM}}, 2, {{PORT_23,7,1,0},{PORT_5,3,1,0}},0},
   {{"vpermq", {OP_MEM, OP_VAL, OP_NON, OP_YMM}}, 2, {{PORT_23,7,1,0},{PORT_5,3,1,0}},0},
   {{"vpermq", {OP_VAL, OP_MEC, OP_NON, OP_YMM}}, 2, {{PORT_23,7,1,0},{PORT_5,3,1,0}},0},
   {{"vpermq", {OP_MEC, OP_VAL, OP_NON, OP_YMM}}, 2, {{PORT_23,7,1,0},{PORT_5,3,1,0}},0},

/* ==================== VPINSRD ==================== */
   {{"vpinsrd", {OP_XMM, OP_REG, OP_VAL, OP_XMM}}, 1, {{PORT_5,3,2,0}},0},
   {{"vpinsrd", {OP_XMM, OP_MEM, OP_VAL, OP_XMM}}, 2, {{PORT_23,6,1,0},{PORT_5,3,1,0}},0},
   {{"vpinsrd", {OP_XMM, OP_MEC, OP_VAL, OP_XMM}}, 2, {{PORT_23,6,1,0},{PORT_5,3,1,0}},0},

/* ==================== NEGL ==================== */
   {{"negl", {OP_NON, OP_NON, OP_NON, OP_REG}}, 1, {{PORT_0156,1,1,0}},IF_TARGET_DEP},
   {{"negl", {OP_NON, OP_NON, OP_NON, OP_MEM}}, 4, {{PORT_23,4,1,0},{PORT_0156,1,1,0},{PORT_237,1,1,MOP_UNCHAINED},{PORT_4,2,1,0}},IF_TARGET_DEP},
   {{"negl", {OP_NON, OP_NON, OP_NON, OP_MEC}}, 4, {{PORT_23,4,1,0},{PORT_0156,1,1,0},{PORT_23,1,1,MOP_UNCHAINED},{PORT_4,2,1,0}},IF_TARGET_DEP},

/* ==================== BLSR ==================== */
   {{"blsr", {OP_REG, OP_NON, OP_NON, OP_REG}}, 1, {{PORT_0156,1,1,0}},0},
   {{"blsr", {OP_MEM, OP_NON, OP_NON, OP_REG}}, 2, {{PORT_23,4,1,0},{PORT_0156,1,1,0}},0},
   {{"blsr", {OP_MEC, OP_NON, OP_NON, OP_REG}}, 2, {{PORT_23,4,1,0},{PORT_0156,1,1,0}},0},

/* ==================== SETLE ==================== */
   {{"setle", {OP_NON, OP_NON, OP_NON, OP_REG}}, 1, {{PORT_0156,1,1,0}},IF_TARGET_DEP},

/* ==================== SETNE ==================== */
   {{"setne", {OP_NON, OP_NON, OP_NON, OP_REG}}, 1, {{PORT_0156,1,1,0}},IF_TARGET_DEP},

/* ==================== IMULL ==================== */
   {{"imull", {OP_REG, OP_NON, OP_NON, OP_REG}}, 1, {{PORT_1,3,1,0}},0},
   {{"imull", {OP_MEM, OP_NON, OP_NON, OP_REG}}, 2, {{PORT_23,4,1,0},{PORT_1,3,1,0}},0},
   {{"imull", {OP_MEC, OP_NON, OP_NON, OP_REG}}, 2, {{PORT_23,4,1,0},{PORT_1,3,1,0}},0},

/* ==================== TZCNT ==================== */
   {{"tzcntw", {OP_REG, OP_NON, OP_NON, OP_REG}}, 1, {{PORT_1,3,1,0}},IF_TARGET_DEP},
   {{"tzcntw", {OP_MEM, OP_NON, OP_NON, OP_REG}}, 2, {{PORT_23,4,1,0},{PORT_1,3,1,0}},IF_TARGET_DEP},
   {{"tzcntw", {OP_MEC, OP_NON, OP_NON, OP_REG}}, 2, {{PORT_23,4,1,0},{PORT_1,3,1,0}},IF_TARGET_DEP},

   {{"tzcntl", {OP_REG, OP_NON, OP_NON, OP_REG}}, 1, {{PORT_1,3,1,0}},0},
   {{"tzcntl", {OP_MEM, OP_NON, OP_NON, OP_REG}}, 2, {{PORT_23,4,1,0},{PORT_1,3,1,0}},0},
   {{"tzcntl", {OP_MEC, OP_NON, OP_NON, OP_REG}}, 2, {{PORT_23,4,1,0},{PORT_1,3,1,0}},0},

   {{"tzcntq", {OP_REG, OP_NON, OP_NON, OP_REG}}, 1, {{PORT_1,3,1,0}},0},
   {{"tzcntq", {OP_MEM, OP_NON, OP_NON, OP_REG}}, 2, {{PORT_23,4,1,0},{PORT_1,3,1,0}},0},
   {{"tzcntq", {OP_MEC, OP_NON, OP_NON, OP_REG}}, 2, {{PORT_23,4,1,0},{PORT_1,3,1,0}},0},

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

/* ==================== VPINSRD ==================== */
   {{"vpinsrd", {OP_VAL,OP_REG, OP_XMM, OP_XMM}}, 2, {{PORT_1,2,1,0},{PORT_5,1,1,0}},0},
   {{"vpinsrd", {OP_VAL,OP_MEM, OP_XMM, OP_XMM}}, 2, {{PORT_23,6,1,0},{PORT_5,1,1,0}},0},
   {{"vpinsrd", {OP_VAL,OP_MEC, OP_XMM, OP_XMM}}, 2, {{PORT_23,6,1,0},{PORT_5,1,1,0}},0},

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

static int _inst_search(FInstruction *inst, FInstructionDef *def, int ops_cnt)
   {
   int low = -1;
   int hi = known_icount;
   int pos = known_icount / 2;
   int res;

   if (ops_cnt && ops_cnt != 4)
      {
      def->operands[3] = def->operands[ops_cnt - 1];
      def->operands[ops_cnt - 1] = OP_NON;
      }

   while ((res = _compare_inst_def(&inst_idx[pos]->def,def)))
      {
      if (res < 0)
         low = pos;
      else
         hi = pos;
      pos = low + (hi - low) / 2;
      if (pos <= low || pos >= hi)
         return 0;
      }
   strcpy(inst->def.mnem,def->mnem);
   if (ops_cnt && ops_cnt != 4 && (inst_idx[pos]->flags & IF_NO_TARGET))
      {
      def->operands[ops_cnt - 1] = def->operands[3];
      def->operands[3] = OP_NON;
      }
   *((uint32_t *)&inst->def.operands) = *((uint32_t *)&def->operands);
   inst->mops_cnt = inst_idx[pos]->mops_cnt;
   inst->ops = inst_idx[pos]->ops;
   inst->targ_dep = inst_idx[pos]->flags & IF_TARGET_DEP;
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

static uint8_t _get_reg(char *string, int *reg)
   {
   *reg = REG_NONE;
   if (!string[0] || !string[1])
      return OP_BAD;
   char ch0 = string[0] | 0x20;
   char ch1 = string[1] | 0x20;
   char ch2 = string[2] | 0x20;
   switch (ch0)
      {
      case 'd':
         if (ch1 == 'i') return *reg = REG_RDI, OP_REG;
         goto low_regs;
      case 's':
         if (ch1 == 'i') return *reg = REG_RSI, OP_REG;
         if (ch1 == 'p') return *reg = REG_NONE, OP_REG;
         return OP_BAD;
      case 'b': 
         if (ch1 == 'p') return *reg = REG_NONE, OP_REG; // Не считаем RBP, RSP т.к. они одинаковы для всех
      case 'a':
      case 'c':
         {
low_regs:
         switch (ch1)
            {
            case 'x': case 'h': case 'l':
               return *reg = REG_RAX + ch0 - 'a', OP_REG;
            }
         return OP_BAD;
         }
      case 'e':
         goto hi_regs;

      case 'x':
         {
         if (ch1 != 'm' && ch2 != 'm')
            return OP_BAD;
         int rnum = strtoul(&string[3],NULL,0);
         if (rnum > 15)
            return OP_BAD;
         return *reg = REG_YMM0 + rnum, OP_XMM;
         }
      case 'y':
         {
         if (ch1 != 'm' && ch2 != 'm')
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
            switch(ch1)
               {
               case 'c':
               case 'a':
                  {
                  if (ch2 == 'x')
                     return *reg = REG_RAX + ch1 - 'a', OP_REG;
                  return OP_BAD;
                  }
               case 'b':
                  {
                  if (ch2 == 'x')
                     return *reg = REG_RBX, OP_REG;
                  if (ch2 == 'p')
                     return *reg = REG_NONE, OP_REG;
                  return OP_BAD;
                  }
               case 'd':
                  {
                  if (ch2 == 'x')
                     return *reg = REG_RDX, OP_REG;
                  if (ch2 == 'i')
                     return *reg = REG_RDI, OP_REG;
                  return OP_BAD;
                  }
               case 's':
                  {
                  if (ch2 == 'i')
                     return *reg = REG_RSI, OP_REG;
                  if (ch2 == 'p')
                     return *reg = REG_NONE, OP_REG;
                  return OP_BAD;
                  }
               case 'i':
                  {
                  if (ch2 == 'p')
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

static uint8_t _get_param_type(char *param,uint64_t *reg_usage)
   {
   int has_shift = 0;
   switch (param[0])
      {
      case '$': // Константа
         return OP_VAL;
      case '%':
         { // Регистр
         int reg = REG_NONE;
         uint8_t rv = _get_reg(&param[1],&reg);
         *reg_usage |= ((uint64_t)(reg != REG_NONE)) << reg;
         return rv;
         }
      case '.':
         {
         param = strpbrk(param,"(,# \t\r\n");
         if (!param || param[0] != '(')
            return OP_MEM;
         has_shift = 1;
         goto bracket;
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
         int reg,ccnt = 0;
         do
            {
            param++;
            param += strspn(param,"\t ");
            if (param[0] == '%')
               {
               _get_reg(param+1,&reg);
               *reg_usage |= ((uint64_t)(reg != REG_NONE)) << reg;
               }
            ccnt++;
            param = strpbrk(param,"),");
            }
         while (param && param[0] != ')');
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
	if (!f)
      {
      printf("can not open file %s\n",filename);
      return NULL;
      }

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

   uint64_t output_regs = 0; // Регистры, которым присвоено значение, но оно не использовано внутри блока = выходные

	for (;fgets(buf,512,f); lnum++)
		{
      FInstructionDef idef = {0};
      uint64_t reg_usages[4] = {0};
      int pts_cnt = 0;

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

      strcpy(idef.mnem,cmd);

      if (lnum == 119)
         lnum = 119;

      do
         {
         idef.operands[pts_cnt] = _get_param_type(pos,&reg_usages[pts_cnt]);
         if (idef.operands[pts_cnt] == OP_BAD)
            {
            printf("%s %d: instruction %s has unknown param format\n",filename,lnum,cmd);
            goto prf_err_exit;
            }
         if (idef.operands[pts_cnt] == OP_NON)
            break;
         pts_cnt++;
         pos = _next_param(pos);
         }
      while (pts_cnt < 4 && pos);


      if (!_inst_search(work,&idef,pts_cnt))
         {
         printf("%s %d: unknown instruction %s\n",filename,lnum,cmd);
         goto prf_err_exit;
         }

      uint64_t reg_usage = 0; // Регистры от которых зависит инструкция
      uint64_t targ_regs = 0; // Регистры в аргументе назначения
      for (i = 0; i < pts_cnt - 1; i++)
         {
         work->def.operands[i] = idef.operands[i];
         reg_usage |= reg_usages[i];
         }
      if (work->def.operands[3])
         targ_regs = reg_usages[i];
      else if (work->def.operands[i])
         reg_usage |= reg_usages[i];

      if (work->def.operands[3] == OP_REG || work->def.operands[3] == OP_XMM || work->def.operands[3] == OP_YMM)
         {
         work->treg = __builtin_ctz(targ_regs);
         output_regs &= ~reg_usage;
         if (work->targ_dep)
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

prf_err_exit:
   if (f) fclose(f);
   if (rv) free(rv);
   return NULL;
   }