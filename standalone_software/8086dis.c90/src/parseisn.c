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

Results ParseInstruction(QueU8 *input, QueU8 *output, X86CpuState *cpu_state)
{
   /* Get first byte */
   u8 opcode_byte = *(input->back);
   OpcodeEntry *opcode_entry = OpcodeTable;
   /* todo binary search? */
   /* linear scan through table with single byte opcodes */
   while (opcode_entry->size == 1) {
      u8 masked_opcode = opcode_byte & opcode_entry->mask[0];
      if (masked_opcode == opcode_entry->data[0]) {
         /* Add check if we have enough bytes in queue for this instruction */
         if (opcode_entry->handler != NULL)
            return opcode_entry->handler(input, output, cpu_state);
      }
      opcode_entry++;
   }
   /* Linear scan through table with double byte opcodes */
   /* Did not find opcode? */
   return ISN_UNKNOWN;
}
