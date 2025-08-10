/*
SPDX-License-Identifier: MIT

Copyright (c) 2025 Bart Bilos
For conditions of distribution and use, see LICENSE file
*/
#ifndef HISNS_H
#define HISNS_H

#include "que8u.h"
#include "results.h"
#include "x86cpu.h"

/* Instruction handler prototypes */
/* For the names we use natural ordering Move from Immediate to Register */
/* Handle moves from accumulator to memory */
Results HandleMovAccMem(QueU8 *input, QueU8 *output, X86CpuState *cpu_state);
/* Handle moves from memory to accumulator */
Results HandleMovMemAcc(QueU8 *input, QueU8 *output, X86CpuState *cpu_state);
/* Handle move from Immediate to register */
Results HandleMovImmReg(QueU8 *input, QueU8 *output, X86CpuState *cpu_state);
Results HandleDas(QueU8 *input, QueU8 *output, X86CpuState *cpu_state);
Results HandleAas(QueU8 *input, QueU8 *output, X86CpuState *cpu_state);
Results HandleAad(QueU8 *input, QueU8 *output, X86CpuState *cpu_state);

#endif
