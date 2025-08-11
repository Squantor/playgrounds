/*
SPDX-License-Identifier: MIT

Copyright (c) 2025 Bart Bilos
For conditions of distribution and use, see LICENSE file
*/
/*
X86 instruction table definitions
*/
#include "x86isn.h"
#include "hisns.h"
#include <stddef.h>

/*
Table of X86 opcodes and their filter masks. MUST BE KEPT SORTED SMALL TO BIG!
Sorting is first done on the mask size, then on the opcode content.
*/
Opcode1Entry Opcode1Table[MAX_OPCODE_SINGLE] = {
    {0xB0, 0xF0, HandleMovImmReg},   /* MOV REG,IMM */
    {0x88, 0xFC, HandleMovModRegRM}, /* MOV ModRegRM */
    {0xA0, 0xFE, HandleMovMemAcc},   /* MOV ACC,MEM */
    {0xA2, 0xFE, HandleMovAccMem},   /* MOV MEM,ACC */
    {0x2F, 0xFF, HandleDas},         /* DAS */
    {0x3F, 0xFF, HandleAas},         /* AAS */
};
/*
Table of X86 opcodes and their filter masks. MUST BE KEPT SORTED SMALL TO BIG!
Sorting is first done on the mask size, then on the opcode content.
*/
Opcode2Entry Opcode2Table[MAX_OPCODE_DOUBLE] = {
    {{0xD5, 0x0A}, {0xFF, 0xFF}, HandleAad}, /* AAD */
};
