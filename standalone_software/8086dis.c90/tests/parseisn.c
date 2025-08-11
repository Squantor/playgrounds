/*
SPDX-License-Identifier: MIT

Copyright (c) 2025 Bart Bilos
For conditions of distribution and use, see LICENSE file
*/
/*
Tests for Instruction parse
*/
#include "parseisn.h"
#include "minunit.h"
#include "mocks.h"
#include "que8u.h"
#include "results.h"
#include "tests.h"
#include "types.h"
#include "x86cpu.h"
#include "x86tok.h"

/* Tests for invalid instruction */
static void TestInvalidInstruction(void)
{
   u8 invalid_isn_bytes[] = {0x60};
   Qu8Reset(&parse_isn_input);
   Qu8Reset(&parse_isn_output);
   Qu8PushFrontBlock(&parse_isn_input, invalid_isn_bytes,
                     sizeof(invalid_isn_bytes));
   ResetParseIsnCpuState();
   MinunitExpect(ParseInstruction(&parse_isn_input, &parse_isn_output,
                                  &parse_isn_cpu_state) == OP_UNKNOWN);
   MinunitExpect(Qu8Level(&parse_isn_output) == 0);
   MinunitExpect(Qu8Level(&parse_isn_input) == 1);
   MinunitExpect(parse_isn_cpu_state.ip == 0x0000);
}
/* Tests for the DAS instructions */
static void TestDas(void)
{
   u8 isn_das[] = {0x2F};
   u8 token = TOK_INVALID;
   Qu8Reset(&parse_isn_input);
   Qu8Reset(&parse_isn_output);
   Qu8PushFrontBlock(&parse_isn_input, isn_das, sizeof(isn_das));
   ResetParseIsnCpuState();
   MinunitExpect(ParseInstruction(&parse_isn_input, &parse_isn_output,
                                  &parse_isn_cpu_state) == READY);
   MinunitExpect(Qu8Level(&parse_isn_output) == 1);
   Qu8PopBack(&parse_isn_output, &token);
   MinunitExpect(token == ISN_DAS);
   MinunitExpect(Qu8Level(&parse_isn_input) == 0);
   MinunitExpect(parse_isn_cpu_state.ip == 0x0001);
}

void TestParseInstruction(void)
{
   TestInvalidInstruction();
   TestDas();
}
