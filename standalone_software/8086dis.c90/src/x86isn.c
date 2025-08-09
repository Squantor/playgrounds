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
OpcodeEntry OpcodeTable[MAX_INSTRUCTIONS] = {
    {{0xA0, 0}, {0xFE, 0}, 1, HandleMovMemAcc}, /* MOV MEM,ACC */
    {{0xA2, 0}, {0xFE, 0}, 1, HandleMovAccMem}, /* MOV ACC,MEM */
    {{0x2F, 0}, {0xFF, 0}, 1, HandleDas},       /* DAS */
    {{0x3F, 0}, {0xFF, 0}, 1, HandleAas},       /* AAS */
    {{0xD5, 0x0A}, {0xFF, 0xFF}, 2, HandleAad}, /* AAD */
};
