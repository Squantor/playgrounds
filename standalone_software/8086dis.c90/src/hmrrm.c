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

Results HandleModRegRM(QueU8 *input, QueU8 *output, X86CpuState *cpu_state)
{
   u8 opcode;
   u8 modregrm;
   u8 to_reg;
   u8 word_op;
   u8 mod;
   u8 reg;
   u8 rm;
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
      return ISN_INVALID;
   return READY;
}
