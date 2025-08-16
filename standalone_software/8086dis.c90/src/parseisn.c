/*
SPDX-License-Identifier: MIT

Copyright (c) 2025 Bart Bilos
For conditions of distribution and use, see LICENSE file
*/
/*
Instruction parser functions
*/
#include "parseisn.h"
#include "que8u.h"
#include "results.h"
#include "types.h"
#include "x86cpu.h"
#include "x86isn.h"
#include <stddef.h>

#ifdef TESTS
/* Incject mocks here */
#endif

/* Go through single byte opcodes to find instruction */
static Results ParseSingleOpcode(QueU8 *input, QueU8 *output,
                                 X86CpuState *cpu_state)
{
   Opcode1Entry *opcode_entry = Opcode1Table;
   u8 opcode;
   u16 i;
   Qu8PeekBack(input, &opcode);
   /* todo binary search? */
   /* linear scan through table with single byte opcodes */
   for (i = 0; i < MAX_OPCODE_SINGLE; i++) {
      u8 masked_opcode = opcode & opcode_entry->mask;
      if (masked_opcode == opcode_entry->data) {
         if (opcode_entry->handler != NULL)
            return opcode_entry->handler(input, output, cpu_state);
      }
      opcode_entry++;
   }
   return OP_UNKNOWN;
}

static Results ParseDoubleOpcode(QueU8 *input, QueU8 *output,
                                 X86CpuState *cpu_state)
{
   Opcode2Entry *opcode_entry = Opcode2Table;
   u8 opcode_buffer[2];
   u16 opcode;
   u16 i;
   Qu8PeekBackBlock(input, opcode_buffer, 2);
   opcode = (u16) ((opcode_buffer[0] << 8) | opcode_buffer[1]);
   /* todo binary search? */
   /* linear scan through table with single byte opcodes */
   for (i = 0; i < MAX_OPCODE_SINGLE; i++) {
      u16 masked_opcode = opcode & opcode_entry->mask;
      if (masked_opcode == opcode_entry->data) {
         if (opcode_entry->handler != NULL)
            return opcode_entry->handler(input, output, cpu_state);
      }
      opcode_entry++;
   }
   return OP_UNKNOWN;
}

Results ParseInstruction(QueU8 *input, QueU8 *output, X86CpuState *cpu_state)
{
   Results result = ParseSingleOpcode(input, output, cpu_state);
   if (result != OP_UNKNOWN)
      return result;
   result = ParseDoubleOpcode(input, output, cpu_state);
   return result;
}
