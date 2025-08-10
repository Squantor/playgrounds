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

/* Handle mod 11: register to register operation */
static Results HandleModRegReg(u8 opcode, u8 modregrm, QueU8 *output,
                               X86CpuState *cpu_state)
{
   u8 to_reg = opcode & OPCODE_DIR_MASK;
   u8 word_op = opcode & OPCODE_SIZE_MASK;
   u8 reg = (u8) ((modregrm & MODREGRM_REG_MASK) >> 3);
   u8 rm = modregrm & MODREGRM_RM_MASK;
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
}

Results HandleModRegRM(u8 opcode, u8 modregrm, QueU8 *output,
                       X86CpuState *cpu_state)
{
   u8 mod = modregrm & MODREGRM_MOD_MASK;
   if (mod == 0xC0) {
      return HandleModRegReg(opcode, modregrm, output, cpu_state);
   } else
      return ISN_UNKNOWN;
   return READY;
}
