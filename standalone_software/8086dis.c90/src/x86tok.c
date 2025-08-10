/*
SPDX-License-Identifier: MIT

Copyright (c) 2025 Bart Bilos
For conditions of distribution and use, see LICENSE file
*/
/*
X86 instruction parser token helper functions
*/
#include "x86tok.h"
#include "que8u.h"
#include "types.h"

/* Lookup tables translating index to register definitions */
static u8 lut_reg16[8] = {REG_AX, REG_CX, REG_DX, REG_BX,
                          REG_SP, REG_BP, REG_SI, REG_DI};
static u8 lut_reg8[8] = {REG_AL, REG_CL, REG_DL, REG_BL,
                         REG_AH, REG_CH, REG_DH, REG_BH};
/*static u8 lut_segreg[4] = {REG_ES, REG_CS, REG_SS, REG_DS};*/

void Create16BitAddrToken(QueU8 *input, QueU8 *output)
{
   u8 address;
   Qu8PushFront(output, ADDR_16B);
   Qu8PopBack(input, &address);
   Qu8PushFront(output, address);
   Qu8PopBack(input, &address);
   Qu8PushFront(output, address);
}

void Create16BitRegisterToken(u8 reg_field, QueU8 *output)
{
   if (reg_field > 7) {
      Qu8PushFront(output, TOK_INVALID);
      return;
   }
   Qu8PushFront(output, lut_reg16[reg_field]);
}

void Create8BitRegisterToken(u8 reg_field, QueU8 *output)
{
   if (reg_field > 7) {
      Qu8PushFront(output, TOK_INVALID);
      return;
   }
   Qu8PushFront(output, lut_reg8[reg_field]);
}

void Create16BitImmediateToken(QueU8 *input, QueU8 *output)
{
   u8 immediate;
   Qu8PushFront(output, IMM_16B);
   Qu8PopBack(input, &immediate);
   Qu8PushFront(output, immediate);
   Qu8PopBack(input, &immediate);
   Qu8PushFront(output, immediate);
}

void Create8BitImmediateToken(QueU8 *input, QueU8 *output)
{
   u8 immediate;
   Qu8PushFront(output, IMM_8B);
   Qu8PopBack(input, &immediate);
   Qu8PushFront(output, immediate);
}