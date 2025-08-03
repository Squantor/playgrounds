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

#include "types.h"

#define MAX_OPCODE_SIZE 2
#define MAX_INSTRUCTIONS 5

typedef void (*OpcodeHandler)(void);

/* Entry in the instruction table to handle an instruction */
typedef struct {
   u8 data[MAX_OPCODE_SIZE]; /* Opcode pattern */
   u8 mask[MAX_OPCODE_SIZE]; /* Opcode mask */
   u8 size;                  /* Size of the opcode */
   OpcodeHandler handler;    /* Handler function for this opcode */
} OpcodeEntry;

extern OpcodeEntry OpcodeTable[MAX_INSTRUCTIONS];

#endif
