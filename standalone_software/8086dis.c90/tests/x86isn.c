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

/* Check if the single byte opcode table is sorted*/
static void TestSortedSingle(void)
{
   u8 prev_data = 0x00;
   u8 prev_mask = 0x00;
   u16 i;
   Opcode1Entry *curr_opcode = Opcode1Table;
   for (i = 0; i < MAX_OPCODE_SINGLE; i++) {
      u8 curr_data = curr_opcode->data;
      u8 curr_mask = curr_opcode->mask;
      /* check ordering */
      MinunitExpect(curr_mask >= prev_mask);
      /* We only check data if the masks are the same */
      if (prev_mask == curr_mask)
         MinunitExpect(curr_data > prev_data);

      prev_data = curr_data;
      prev_mask = curr_mask;
      curr_opcode++;
   }
}

/* Check if the double byte opcode table is sorted*/
static void TestSortedDouble(void)
{
   u16 prev_data = 0x0000;
   u16 prev_mask = 0x0000;
   u16 i;
   Opcode2Entry *curr_opcode = Opcode2Table;
   for (i = 0; i < MAX_OPCODE_DOUBLE; i++) {
      /* Collect masks/data */
      u16 curr_data = curr_opcode->data;
      u16 curr_mask = curr_opcode->mask;
      /* check ordering */
      MinunitExpect(curr_mask >= prev_mask);
      /* We only check data if the masks are the same */
      if (prev_mask == curr_mask)
         MinunitExpect(curr_data > prev_data);
      prev_data = curr_data;
      prev_mask = curr_mask;
      curr_opcode++;
   }
}

void TestX86IsnTable(void)
{
   TestSortedSingle();
   TestSortedDouble();
}
