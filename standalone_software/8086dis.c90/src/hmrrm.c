/*
SPDX-License-Identifier: MIT

Copyright (c) 2025 Bart Bilos
For conditions of distribution and use, see LICENSE file
*/
/*
Handler for all the ModRegR/M byte
*/
#include "hisns.h"
#include "que8u.h"
#include "results.h"
#include "types.h"
#include "x86cpu.h"
#include "x86tok.h"

static void HandleRMField(u8 mod, u8 rm, QueU8 *input, QueU8 *output,
                          X86CpuState *cpu_state)
{
   /* Special case of mod 0 with BP address, emit memory address */
   if (mod == 0x00 && rm == 0x06) {
      Create16BitAddrToken(input, output);
      cpu_state->ip += 4;
      return;
   }
   CreateRMAddressingTokens(rm, output);
   /* Emit displacement if any */
   if (mod == 0x00) {
      Qu8PushFront(output, ADDR_END); /* No displacement needed */
      cpu_state->ip += 2;
   } else if (mod == 0x40) {
      Create8BitDisplacementToken(input, output);
      cpu_state->ip += 3;
   } else if (mod == 0x80) {
      Create16BitDisplacementToken(input, output);
      cpu_state->ip += 4;
   }
}

Results HandleModRegRM(QueU8 *input, QueU8 *output, X86CpuState *cpu_state)
{
   u8 opcode, modregrm;
   u8 to_reg, word_op;
   u8 mod, reg, rm;
   /* todo: I miss a simpler popback here */
   Qu8PopBack(input, &opcode);
   Qu8PopBack(input, &modregrm);
   to_reg = opcode & OPCODE_DIR_MASK;
   word_op = opcode & OPCODE_SIZE_MASK;
   mod = (u8) (modregrm & MODREGRM_MOD_MASK);
   reg = (u8) ((modregrm & MODREGRM_REG_MASK) >> 3);
   rm = modregrm & MODREGRM_RM_MASK;
   /* Handle mod 11: register to register operation */
   if (mod == 0xC0) {
      if (word_op) {
         if (to_reg) {
            Create16BitRegisterToken(reg, output);
            Create16BitRegisterToken(rm, output);
         } else {
            Create16BitRegisterToken(rm, output);
            Create16BitRegisterToken(reg, output);
         }
      } else {
         if (to_reg) {
            Create8BitRegisterToken(reg, output);
            Create8BitRegisterToken(rm, output);
         } else {
            Create8BitRegisterToken(rm, output);
            Create8BitRegisterToken(reg, output);
         }
      }
      cpu_state->ip += 2;
      return READY;
   } else
   /* Handle mod 00, 01, 10: addressing mode */
   {
      if (word_op) {
         if (to_reg) {
            Create16BitRegisterToken(reg, output);
            HandleRMField(mod, rm, input, output, cpu_state);
         } else {
            HandleRMField(mod, rm, input, output, cpu_state);
            Create16BitRegisterToken(reg, output);
         }
      } else {
         if (to_reg) {
            Create8BitRegisterToken(reg, output);
            HandleRMField(mod, rm, input, output, cpu_state);
         } else {
            HandleRMField(mod, rm, input, output, cpu_state);
            Create8BitRegisterToken(reg, output);
         }
      }
      return READY;
   }
   return ISN_INVALID;
}
