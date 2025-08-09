/*
SPDX-License-Identifier: MIT

Copyright (c) 2025 Bart Bilos
For conditions of distribution and use, see LICENSE file
*/
/*
Handler for all the Decimal adjust instructions
*/
#include "que8u.h"
#include "results.h"
#include "x86cpu.h"

/* Handle Decimal Adjust for Subtract */
Results HandleDas(QueU8 *input, QueU8 *output, X86CpuState *cpu_state)
{
   (void) input;
   (void) output;
   (void) cpu_state;
   return READY;
}
