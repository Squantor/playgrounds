/*
SPDX-License-Identifier: MIT

Copyright (c) 2025 Bart Bilos
For conditions of distribution and use, see LICENSE file
*/
/*
Instruction parser definitions
*/
#ifndef PARSEISN_H
#define PARSEISN_H

#include "que8u.h"
#include "results.h"
#include "types.h"
#include "x86cpu.h"

/* Interpret enough bytes from the input queue so one instruction is decoded.
Decode result is put in the output queue in the form of decoded instruction
enum values.
The instruction decode will also update the cpu state if needed.
Result READY when instruction was parsed succesfully and ready for next one
Result ISN_UNKNOWN when instruction is invalid */
Results ParseInstruction(QueU8 *input, QueU8 *output, X86CpuState *cpu_state);

#endif
