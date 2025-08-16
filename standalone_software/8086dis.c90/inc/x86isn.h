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

#define MAX_OPCODE_SINGLE 8 /* Maximum single byte opcodes */
#define MAX_OPCODE_DOUBLE 1 /* Maximum double byte opcodes */

typedef Results (*OpcodeHandler)(QueU8 *input, QueU8 *output,
                                 X86CpuState *cpu_state);

/* Single byte opcode entry for the single byte instruction table */
typedef struct {
   u8 data;               /* Opcode pattern */
   u8 mask;               /* Opcode mask */
   OpcodeHandler handler; /* Handler function for this opcode */
} Opcode1Entry;

/* double byte opcode entry for the two byte instruction table */
typedef struct {
   u8 data[2];            /* Opcode pattern */
   u8 mask[2];            /* Opcode mask */
   OpcodeHandler handler; /* Handler function for this opcode */
} Opcode2Entry;

extern Opcode1Entry Opcode1Table[MAX_OPCODE_SINGLE];
extern Opcode2Entry Opcode2Table[MAX_OPCODE_DOUBLE];

#endif
