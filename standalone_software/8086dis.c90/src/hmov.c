/*
SPDX-License-Identifier: MIT

Copyright (c) 2025 Bart Bilos
For conditions of distribution and use, see LICENSE file
*/
/*
Handler for all the MOV instructions
*/
#include "que8u.h"
#include "results.h"
#include "x86cpu.h"
#include "x86isn.h"
#include "x86tok.h"

Results HandleMovImmReg(QueU8 *input, QueU8 *output, X86CpuState *cpu_state)
{
   u8 opcode;
   u8 word_op; /* word operation */
   Qu8PopBack(input, &opcode);
   word_op = opcode & 0x08;
   Qu8PushFront(output, ISN_MOV);
   if (word_op) {
      Create16BitRegisterToken(opcode & 0x7, output);
      Create16BitImmediateToken(input, output);
      cpu_state->ip += 3;
   } else {
      Create8BitRegisterToken(opcode & 0x7, output);
      Create8BitImmediateToken(input, output);
      cpu_state->ip += 2;
   }
   return READY;
}

Results HandleMovAccMem(QueU8 *input, QueU8 *output, X86CpuState *cpu_state)
{
   u8 opcode;
   Qu8PopBack(input, &opcode);
   Qu8PushFront(output, ISN_MOV);
   Create16BitAddrToken(input, output);
   if (opcode & ISN_SIZE_MASK) {
      Qu8PushFront(output, REG_AX);
   } else {
      Qu8PushFront(output, REG_AL);
   }
   cpu_state->ip += 3;
   return READY;
}

Results HandleMovMemAcc(QueU8 *input, QueU8 *output, X86CpuState *cpu_state)
{
   u8 opcode;
   Qu8PopBack(input, &opcode);
   Qu8PushFront(output, ISN_MOV);
   if (opcode & ISN_SIZE_MASK) {
      Qu8PushFront(output, REG_AX);
   } else {
      Qu8PushFront(output, REG_AL);
   }
   Create16BitAddrToken(input, output);
   cpu_state->ip += 3;
   return READY;
}
