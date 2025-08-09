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

typedef enum {
   TOK_INVALID,
   /* instruction tokens */
   ISN_DAS, /* DAS instruction */
   ISN_AAS, /* AAS instruction */
   ISN_AAD, /* AAD instruction */
   /* Operand tokens */
   /* Other tokens */
   ADDR_16B, /* 16-bit address */
   ADDR_20B  /* 20-bit address */
} X86Token;

#endif
