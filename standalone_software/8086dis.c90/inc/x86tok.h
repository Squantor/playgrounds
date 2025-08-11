/*
SPDX-License-Identifier: MIT

Copyright (c) 2025 Bart Bilos
For conditions of distribution and use, see LICENSE file
*/
/*
X86 instruction parser token definitions
*/
#ifndef X86TOK_H
#define X86TOK_H

#include "que8u.h"

typedef enum {
   TOK_INVALID,
   /* instruction tokens */
   ISN_DAS, /* DAS instruction */
   ISN_AAS, /* AAS instruction */
   ISN_AAD, /* AAD instruction */
   ISN_MOV, /* MOV instruction */
   /* Operand tokens */
   REG_AX, /* AX register */
   REG_BX, /* BX register */
   REG_CX, /* CX register */
   REG_DX, /* DX register */
   REG_SI, /* SI register */
   REG_DI, /* DI register */
   REG_BP, /* BP register */
   REG_SP, /* SP register */
   REG_AL, /* AL register */
   REG_AH, /* AH register */
   REG_BL, /* BL register */
   REG_BH, /* BH register */
   REG_CL, /* CL register */
   REG_CH, /* CH register */
   REG_DL, /* DL register */
   REG_DH, /* DH register */
   REG_CS, /* CS register */
   REG_DS, /* DS register */
   REG_ES, /* ES register */
   REG_SS, /* SS register */
   /* Addressing mode tokens */
   ADDR_START, /* Addressing mode start */
   ADDR_END,   /* Addressing mode end */
   OP_ADD,     /* Add operation */
   DISP_8B,    /* 8-bit displacement */
   DISP_16B,   /* 16-bit displacement */
   /* Other tokens */
   IMM_8B,   /* 8-bit immediate */
   IMM_16B,  /* 16-bit immediate */
   ADDR_16B, /* 16-bit address */
   ADDR_20B  /* 20-bit address */

} X86Token;

/* Get 2 instruction bytes and output 16bit address token with address */
void Create16BitAddrToken(QueU8 *input, QueU8 *output);
/* Get 1 instruction byte and output 8 bit immediate token */
void Create8BitImmediateToken(QueU8 *input, QueU8 *output);
/* get 2 instruction bytes and output 16bit immediate token */
void Create16BitImmediateToken(QueU8 *input, QueU8 *output);
/* get register field and output 16 bit register token */
void Create16BitRegisterToken(u8 reg_field, QueU8 *output);
/* get register field and output 8 bit register token */
void Create8BitRegisterToken(u8 reg_field, QueU8 *output);
/* Parse R/M field and generate register indexing tokens */
void CreateRMAddressingTokens(u8 rm_field, QueU8 *output);
/* Get 1 byte and Generate a 8 bit displacement tokens */
void Create8BitDisplacementToken(QueU8 *input, QueU8 *output);
/* Get 2 bytes and generate a 16 bit displacement tokens */
void Create16BitDisplacementToken(QueU8 *input, QueU8 *output);

#endif
