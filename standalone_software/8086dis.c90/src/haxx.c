/*
SPDX-License-Identifier: MIT

Copyright (c) 2025 Bart Bilos
For conditions of distribution and use, see LICENSE file
*/
/*
Handler for all the ASCII adjust instructions
*/
#include "que8u.h"
#include "results.h"
#include "x86cpu.h"

/* Handle ASCII Adjust for Subtract */
Results HandleAas(QueU8 *input, QueU8 *output, X86CpuState *cpu_state)
{
   (void) input;
   (void) output;
   (void) cpu_state;
   return READY;
}

/* Handle ASCII Adjust for Divide */
Results HandleAad(QueU8 *input, QueU8 *output, X86CpuState *cpu_state)
{
   (void) input;
   (void) output;
   (void) cpu_state;
   return READY;
}
