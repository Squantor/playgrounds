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
#include "que8u.h"
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

/* Tests for moves with ModRegR/M from addressing mode to register */
/* MOV AH, [BX], MOV BL, [0x1234], MOV CX, [BP+SI+-4], MOV DX, [SI+0x1234] */
static void TestMovMRRMMemReg(void)
{
   u8 mov_mrrm_mem2reg_isns[] = {0x8A, 0x27, 0x8A, 0x1E, 0x34, 0x12, 0x8B,
                                 0x4A, 0xFC, 0x8B, 0x94, 0x34, 0x12};
   u8 mov_mrrm_mem2reg_toks[] = {
       ISN_MOV,    REG_AH,   ADDR_START, REG_BX,  ADDR_END, ISN_MOV,
       REG_BL,     ADDR_16B, 0x34,       0x12,    ISN_MOV,  REG_CX,
       ADDR_START, REG_BP,   REG_SI,     DISP_8B, 0xFC,     ADDR_END,
       ISN_MOV,    REG_DX,   ADDR_START, REG_SI,  DISP_16B, 0x34,
       0x12,       ADDR_END};
   u8 tokens[26], i;
   memset(tokens, TOK_INVALID, sizeof(tokens));
   Qu8Reset(&parse_isn_input);
   Qu8Reset(&parse_isn_output);
   Qu8PushFrontBlock(&parse_isn_input, mov_mrrm_mem2reg_isns,
                     sizeof(mov_mrrm_mem2reg_isns));
   ResetParseIsnCpuState();
   /* Parse four times for all instructions */
   MinunitExpect(ParseInstruction(&parse_isn_input, &parse_isn_output,
                                  &parse_isn_cpu_state) == READY);
   MinunitExpect(ParseInstruction(&parse_isn_input, &parse_isn_output,
                                  &parse_isn_cpu_state) == READY);
   MinunitExpect(ParseInstruction(&parse_isn_input, &parse_isn_output,
                                  &parse_isn_cpu_state) == READY);
   MinunitExpect(ParseInstruction(&parse_isn_input, &parse_isn_output,
                                  &parse_isn_cpu_state) == READY);
   MinunitAssert(Qu8Level(&parse_isn_output) == 26);
   MinunitAssert(Qu8Level(&parse_isn_input) == 0);
   MinunitExpect(parse_isn_cpu_state.ip == 13);
   Qu8PopBackBlock(&parse_isn_output, tokens, sizeof(tokens));
   for (i = 0; i < sizeof(tokens); i++) {
      MinunitExpect(tokens[i] == mov_mrrm_mem2reg_toks[i]);
   }
}
/* Tests for moves with ModRegR/M from register to addressing mode */
static void TestMovMRRMRegMem(void)
{
   u8 mov_mrrm_reg2mem_isns[] = {0x88, 0x34, 0x88, 0x0E, 0x69, 0x25, 0x89,
                                 0xB9, 0x60, 0xF0, 0x89, 0x63, 0x2C};
   u8 mov_mrrm_reg2mem_toks[] = {
       ISN_MOV,  ADDR_START, REG_SI,  ADDR_END, REG_DH,     ISN_MOV, ADDR_16B,
       0x69,     0x25,       REG_CL,  ISN_MOV,  ADDR_START, REG_BX,  REG_DI,
       DISP_16B, 0x60,       0xF0,    ADDR_END, REG_DI,     ISN_MOV, ADDR_START,
       REG_BP,   REG_DI,     DISP_8B, 0x2C,     ADDR_END,   REG_SP};
   u8 tokens[27], i;
   memset(tokens, TOK_INVALID, sizeof(tokens));
   Qu8Reset(&parse_isn_input);
   Qu8Reset(&parse_isn_output);
   Qu8PushFrontBlock(&parse_isn_input, mov_mrrm_reg2mem_isns,
                     sizeof(mov_mrrm_reg2mem_isns));
   ResetParseIsnCpuState();
   /* Parse four times for all instructions */
   MinunitExpect(ParseInstruction(&parse_isn_input, &parse_isn_output,
                                  &parse_isn_cpu_state) == READY);
   MinunitExpect(ParseInstruction(&parse_isn_input, &parse_isn_output,
                                  &parse_isn_cpu_state) == READY);
   MinunitExpect(ParseInstruction(&parse_isn_input, &parse_isn_output,
                                  &parse_isn_cpu_state) == READY);
   MinunitExpect(ParseInstruction(&parse_isn_input, &parse_isn_output,
                                  &parse_isn_cpu_state) == READY);
   MinunitAssert(Qu8Level(&parse_isn_output) == 27);
   MinunitAssert(Qu8Level(&parse_isn_input) == 0);
   MinunitExpect(parse_isn_cpu_state.ip == 13);
   Qu8PopBackBlock(&parse_isn_output, tokens, sizeof(tokens));
   for (i = 0; i < sizeof(tokens); i++) {
      MinunitExpect(tokens[i] == mov_mrrm_reg2mem_toks[i]);
   }
}

void TestMovDisassembly(void)
{
   TestMovAccMem();
   TestMovMemAcc();
   TestMovImmReg();
   TestMovRegReg();
   TestMovMRRMRegMem();
   TestMovMRRMMemReg();
}
