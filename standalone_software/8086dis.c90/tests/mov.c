/*
SPDX-License-Identifier: MIT

Copyright (c) 2025 Bart Bilos
For conditions of distribution and use, see LICENSE file
*/
/*
Tests for MOV instructions
*/
#include "minunit.h"
#include "mocks.h"
#include "parseisn.h"
#include "results.h"
#include "tests.h"
#include "types.h"
#include "x86tok.h"
#include <string.h>

/* Tests for moves from memory to accumulator */
static void TestMovAccMem(void)
{
   u8 mov_mem2a_isns[] = {0xA0, 0x12, 0x34, 0xA1, 0x56, 0x78};
   u8 mov_mem2a_toks[] = {ISN_MOV, REG_AL, ADDR_16B, 0x12, 0x34,
                          ISN_MOV, REG_AX, ADDR_16B, 0x56, 0x78};
   u8 tokens[10];
   u8 i;
   memset(tokens, TOK_INVALID, sizeof(tokens));
   Qu8Reset(&parse_isn_input);
   Qu8Reset(&parse_isn_output);
   Qu8PushFrontBlock(&parse_isn_input, mov_mem2a_isns, sizeof(mov_mem2a_isns));
   ResetParseIsnCpuState();
   /* Parse twice for both byte and word move to accumulator from memory */
   MinunitExpect(ParseInstruction(&parse_isn_input, &parse_isn_output,
                                  &parse_isn_cpu_state) == READY);
   MinunitExpect(ParseInstruction(&parse_isn_input, &parse_isn_output,
                                  &parse_isn_cpu_state) == READY);
   MinunitAssert(Qu8Level(&parse_isn_output) == 10);
   MinunitAssert(Qu8Level(&parse_isn_input) == 0);
   MinunitExpect(parse_isn_cpu_state.ip == 0x0006);
   Qu8PopBackBlock(&parse_isn_output, tokens, sizeof(tokens));
   for (i = 0; i < sizeof(tokens); i++) {
      MinunitExpect(tokens[i] == mov_mem2a_toks[i]);
   }
}
/* Tests for moves from accumulator to memory */
static void TestMovMemAcc(void)
{
   u8 mov_mem2a_isns[] = {0xA2, 0x23, 0x45, 0xA3, 0xAB, 0xCD};
   u8 mov_mem2a_toks[] = {ISN_MOV, ADDR_16B, 0x23, 0x45, REG_AL,
                          ISN_MOV, ADDR_16B, 0xAB, 0xCD, REG_AX};
   u8 tokens[10];
   u8 i;
   memset(tokens, TOK_INVALID, sizeof(tokens));
   Qu8Reset(&parse_isn_input);
   Qu8Reset(&parse_isn_output);
   Qu8PushFrontBlock(&parse_isn_input, mov_mem2a_isns, sizeof(mov_mem2a_isns));
   ResetParseIsnCpuState();
   /* Parse twice for both byte and word move memory to accumulator */
   MinunitExpect(ParseInstruction(&parse_isn_input, &parse_isn_output,
                                  &parse_isn_cpu_state) == READY);
   MinunitExpect(ParseInstruction(&parse_isn_input, &parse_isn_output,
                                  &parse_isn_cpu_state) == READY);
   MinunitAssert(Qu8Level(&parse_isn_output) == 10);
   MinunitAssert(Qu8Level(&parse_isn_input) == 0);
   MinunitExpect(parse_isn_cpu_state.ip == 0x0006);
   Qu8PopBackBlock(&parse_isn_output, tokens, sizeof(tokens));
   for (i = 0; i < sizeof(tokens); i++) {
      MinunitExpect(tokens[i] == mov_mem2a_toks[i]);
   }
}
/* Tests for moves from immediate to register */
static void TestMovImmReg(void)
{
   u8 mov_imm2reg_isns[] = {0xB5, 0x42, 0xBA, 0x01, 0x44};
   u8 mov_imm2reg_toks[] = {ISN_MOV, REG_CH,  IMM_8B, 0x42, ISN_MOV,
                            REG_DX,  IMM_16B, 0x01,   0x44};
   u8 tokens[9];
   u8 i;
   memset(tokens, TOK_INVALID, sizeof(tokens));
   Qu8Reset(&parse_isn_input);
   Qu8Reset(&parse_isn_output);
   Qu8PushFrontBlock(&parse_isn_input, mov_imm2reg_isns,
                     sizeof(mov_imm2reg_isns));
   ResetParseIsnCpuState();
   /* Parse twice for both byte and word move immediate to register */
   MinunitExpect(ParseInstruction(&parse_isn_input, &parse_isn_output,
                                  &parse_isn_cpu_state) == READY);
   MinunitExpect(ParseInstruction(&parse_isn_input, &parse_isn_output,
                                  &parse_isn_cpu_state) == READY);
   MinunitAssert(Qu8Level(&parse_isn_output) == 9);
   MinunitAssert(Qu8Level(&parse_isn_input) == 0);
   MinunitExpect(parse_isn_cpu_state.ip == 0x0005);
   Qu8PopBackBlock(&parse_isn_output, tokens, sizeof(tokens));
   for (i = 0; i < sizeof(tokens); i++) {
      MinunitExpect(tokens[i] == mov_imm2reg_toks[i]);
   }
}
/* Tests for moves from register to register */
static void TestMovRegReg(void)
{
   u8 mov_imm2reg_isns[] = {0x88, 0xEA, 0x89, 0xCF};
   u8 mov_imm2reg_toks[] = {ISN_MOV, REG_DL, REG_CH, ISN_MOV, REG_DI, REG_CX};
   u8 tokens[6];
   u8 i;
   memset(tokens, TOK_INVALID, sizeof(tokens));
   Qu8Reset(&parse_isn_input);
   Qu8Reset(&parse_isn_output);
   Qu8PushFrontBlock(&parse_isn_input, mov_imm2reg_isns,
                     sizeof(mov_imm2reg_isns));
   ResetParseIsnCpuState();
   /* Parse twice for both byte and word move register to register */
   MinunitExpect(ParseInstruction(&parse_isn_input, &parse_isn_output,
                                  &parse_isn_cpu_state) == READY);
   MinunitExpect(ParseInstruction(&parse_isn_input, &parse_isn_output,
                                  &parse_isn_cpu_state) == READY);
   MinunitAssert(Qu8Level(&parse_isn_output) == 6);
   MinunitAssert(Qu8Level(&parse_isn_input) == 0);
   MinunitExpect(parse_isn_cpu_state.ip == 0x0004);
   Qu8PopBackBlock(&parse_isn_output, tokens, sizeof(tokens));
   for (i = 0; i < sizeof(tokens); i++) {
      MinunitExpect(tokens[i] == mov_imm2reg_toks[i]);
   }
}

void TestMovDisassembly(void)
{
   TestMovAccMem();
   TestMovMemAcc();
   TestMovImmReg();
   TestMovRegReg();
}
