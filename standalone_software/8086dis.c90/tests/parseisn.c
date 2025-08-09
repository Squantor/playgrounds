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
#include "que8u.h"
#include "results.h"
#include "tests.h"
#include "types.h"
#include "x86cpu.h"

static u8 parse_isn_input_data[32];
static u8 parse_isn_output_data[32];

static QueU8 parse_isn_input = {
    parse_isn_input_data, parse_isn_input_data, parse_isn_input_data,
    parse_isn_input_data + sizeof(parse_isn_input_data)};
static QueU8 parse_isn_output = {
    parse_isn_output_data, parse_isn_output_data, parse_isn_output_data,
    parse_isn_output_data + sizeof(parse_isn_output_data)};

static X86CpuState parse_isn_cpu_state;

static void ResetParseIsnCpuState(void)
{
   parse_isn_cpu_state.ip = 0x0000;
   parse_isn_cpu_state.cs = 0x0000;
   parse_isn_cpu_state.ds = 0x0000;
   parse_isn_cpu_state.es = 0x0000;
   parse_isn_cpu_state.ss = 0x0000;
}

/* Tests for invalid instructions */
static void TestInvalidInstruction(void)
{
   u8 invalid_isn_bytes[] = {0x60};
   Qu8Reset(&parse_isn_input);
   Qu8Reset(&parse_isn_output);
   Qu8PushFrontBlock(&parse_isn_input, invalid_isn_bytes,
                     sizeof(invalid_isn_bytes));
   ResetParseIsnCpuState();
   MinunitExpect(ParseInstruction(&parse_isn_input, &parse_isn_output,
                                  &parse_isn_cpu_state) == ISN_UNKNOWN);
   MinunitExpect(Qu8Level(&parse_isn_output) == 0);
   MinunitExpect(Qu8Level(&parse_isn_input) == 1);
   MinunitExpect(parse_isn_cpu_state.ip == 0x0000);
}

void TestParseInstruction(void)
{
   TestInvalidInstruction();
}
