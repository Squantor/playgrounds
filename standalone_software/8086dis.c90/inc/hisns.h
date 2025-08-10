/*
SPDX-License-Identifier: MIT

Copyright (c) 2025 Bart Bilos
For conditions of distribution and use, see LICENSE file
*/
/*
Definition of instruction handlers and constants
*/
#ifndef HISNS_H
#define HISNS_H

#include "que8u.h"
#include "results.h"
#include "x86cpu.h"

/* Instruction masks/constants */
#define OPCODE_SIZE_MASK 0x01  /* Mask for byte/word size */
#define OPCODE_DIR_MASK 0x02   /* Mask for to register direction */
#define MODREGRM_MOD_MASK 0xC0 /* Mask for Mod of ModRegR/M byte */
#define MODREGRM_REG_MASK 0x38 /* Mask for Reg of ModRegR/M byte */
#define MODREGRM_RM_MASK 0x07  /* Mask for R/M of ModRegR/M byte */

/* Instruction handler prototypes */
/* For the names we use natural ordering Move from Immediate to Register */
/* Handle moves from accumulator to memory */
Results HandleMovAccMem(QueU8 *input, QueU8 *output, X86CpuState *cpu_state);
/* Handle moves from memory to accumulator */
Results HandleMovMemAcc(QueU8 *input, QueU8 *output, X86CpuState *cpu_state);
/* Handle move from Immediate to register */
Results HandleMovImmReg(QueU8 *input, QueU8 *output, X86CpuState *cpu_state);
/* Handle move with Mod/Reg/RM byte */
Results HandleMovModRegRM(QueU8 *input, QueU8 *output, X86CpuState *cpu_state);
Results HandleDas(QueU8 *input, QueU8 *output, X86CpuState *cpu_state);
Results HandleAas(QueU8 *input, QueU8 *output, X86CpuState *cpu_state);
Results HandleAad(QueU8 *input, QueU8 *output, X86CpuState *cpu_state);

/* Sub handlers */
/* Handle general ModRegR/M byte */
Results HandleModRegRM(u8 opcode, u8 modregrm, QueU8 *output,
                       X86CpuState *cpu_state);

#endif
