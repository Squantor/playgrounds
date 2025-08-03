/*
SPDX-License-Identifier: MIT

Copyright (c) 2025 Bart Bilos
For conditions of distribution and use, see LICENSE file
*/
/*
Tests for x86 instruction table
*/
#include "x86isn.h"

#include "minunit.h"
#include "tests.h"
#include "types.h"

/* Check if the X86 instruction table is sorted*/
void TestSorted(void)
{
   u8 prev_size = 0; /* Previous size */
   u16 prev_data = 0x0000;
   u16 prev_mask = 0xFFFF;
   u16 i, j;
   OpcodeEntry *curr_opcode = OpcodeTable;
   for (i = 0; i < MAX_INSTRUCTIONS; i++) {
      u16 curr_data = 0;
      u16 curr_mask;
      /* Check if size is sorted */
      MinunitExpect(curr_opcode->size >= prev_size);
      /* Collect masks/data */
      curr_mask = ~(u16) ((curr_opcode->mask[0] << 8) | curr_opcode->mask[1]);
      for (j = 0; j < curr_opcode->size; j++) {
         curr_data = (u16) (curr_data << 8);
         curr_data |= curr_opcode->data[j];
      }
      /* check ordering */
      /* We only check data if the masks are the same */
      if (prev_mask == curr_mask)
         MinunitExpect(curr_data > prev_data);
      MinunitExpect(curr_mask <= prev_mask);
      prev_data = curr_data;
      prev_mask = curr_mask;
      prev_size = curr_opcode->size;
      curr_opcode++;
   }
}

void TestX86IsnTable(void)
{
   TestSorted();
}