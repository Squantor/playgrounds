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
#include "x86tok.h"

/* Handle Decimal Adjust for Subtract */
Results HandleDas(QueU8 *input, QueU8 *output, X86CpuState *cpu_state)
{
   Qu8DropBack(input);
   Qu8PushFront(output, ISN_DAS);
   cpu_state->ip++;
   return READY;
}
