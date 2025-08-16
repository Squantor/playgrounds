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
static u8 lut_segreg[4] = {REG_ES, REG_CS, REG_SS, REG_DS};

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

void CreateSegRegToken(u8 reg_field, QueU8 *output)
{
   if (reg_field > 3) {
      Qu8PushFront(output, TOK_INVALID);
      return;
   }
   Qu8PushFront(output, lut_segreg[reg_field]);
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

void CreateRMAddressingTokens(u8 rm_field, QueU8 *output)
{
   switch (rm_field) {
   case 0x00: /* Case [BX+SI] */
      Qu8PushFront(output, ADDR_START);
      Qu8PushFront(output, REG_BX);
      Qu8PushFront(output, REG_SI);
      break;
   case 0x01: /* Case [BX+DI] */
      Qu8PushFront(output, ADDR_START);
      Qu8PushFront(output, REG_BX);
      Qu8PushFront(output, REG_DI);
      break;
   case 0x02: /* Case [BP+SI] */
      Qu8PushFront(output, ADDR_START);
      Qu8PushFront(output, REG_BP);
      Qu8PushFront(output, REG_SI);
      break;
   case 0x03: /* Case [BP+DI] */
      Qu8PushFront(output, ADDR_START);
      Qu8PushFront(output, REG_BP);
      Qu8PushFront(output, REG_DI);
      break;
   case 0x04: /* Case [SI] */
      Qu8PushFront(output, ADDR_START);
      Qu8PushFront(output, REG_SI);
      break;
   case 0x05: /* Case [DI] */
      Qu8PushFront(output, ADDR_START);
      Qu8PushFront(output, REG_DI);
      break;
   case 0x06: /* Case [BP] */
      Qu8PushFront(output, ADDR_START);
      Qu8PushFront(output, REG_BP);
      break;
   case 0x07: /* Case [BX] */
      Qu8PushFront(output, ADDR_START);
      Qu8PushFront(output, REG_BX);
      break;

   default:
      Qu8PushFront(output, TOK_INVALID);
      break;
   }
}

void Create8BitDisplacementToken(QueU8 *input, QueU8 *output)
{
   u8 displacement;
   Qu8PushFront(output, DISP_8B);
   Qu8PopBack(input, &displacement);
   Qu8PushFront(output, displacement);
   Qu8PushFront(output, ADDR_END);
}

void Create16BitDisplacementToken(QueU8 *input, QueU8 *output)
{
   u8 displacement;
   Qu8PushFront(output, DISP_16B);
   Qu8PopBack(input, &displacement);
   Qu8PushFront(output, displacement);
   Qu8PopBack(input, &displacement);
   Qu8PushFront(output, displacement);
   Qu8PushFront(output, ADDR_END);
}
