/*
SPDX-License-Identifier: MIT

Copyright (c) 2025 Bart Bilos
For conditions of distribution and use, see LICENSE file
*/
/*
X86 instruction table definitions
*/
#ifndef X86ISN_H
#define X86ISN_H

#include "que8u.h"
#include "results.h"
#include "types.h"
#include "x86cpu.h"

#define MAX_OPCODE_SIZE 2
#define MAX_INSTRUCTIONS 6
/* Instruction masks/constants */
#define ISN_SIZE_MASK 0x01 /* Mask for byte/word size */

typedef Results (*OpcodeHandler)(QueU8 *input, QueU8 *output,
                                 X86CpuState *cpu_state);

/* Entry in the instruction table to handle an instruction */
typedef struct {
   u8 data[MAX_OPCODE_SIZE]; /* Opcode pattern */
   u8 mask[MAX_OPCODE_SIZE]; /* Opcode mask */
   u8 size;                  /* Size of the opcode */
   /* Size of the total instruction? Not always possible to know forehand */
   OpcodeHandler handler; /* Handler function for this opcode */
} OpcodeEntry;

extern OpcodeEntry OpcodeTable[MAX_INSTRUCTIONS];

#endif
