/*
SPDX-License-Identifier: MIT

Copyright (c) 2025 Bart Bilos
For conditions of distribution and use, see LICENSE file
*/
/*
Instruction parser functions
*/
#include "parseisn.h"
#include "results.h"
#include "types.h"
#include "x86isn.h"
#include <stddef.h>

#ifdef TESTS
/* Incject mocks here */
#endif

Results ParseInstruction(u8 *data, u8 data_size, u8 *new_index)
{
   /* Get first byte */
   u8 opcode_byte = *data;
   OpcodeEntry *opcode_entry = OpcodeTable;
   /* todo binary search? */
   /* linear scan through table with single byte opcodes */
   while (opcode_entry->size == 1) {
      u8 masked_opcode = opcode_byte & opcode_entry->mask[0];
      if (masked_opcode == opcode_entry->data[0])
         if (opcode_entry->handler != NULL)
            opcode_entry->handler();
   }
   /* Linear scan through table with double byte opcodes */

   /* found match? Call handler */
   /* Not found? report error */
   return READY;
}
