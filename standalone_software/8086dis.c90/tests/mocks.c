/*
SPDX-License-Identifier: MIT

Copyright (c) 2025 Bart Bilos
For conditions of distribution and use, see LICENSE file
*/
/*
Mocks and helper functions definitions
*/
#include "mocks.h"
#include "que8u.h"
#include "types.h"
#include "x86cpu.h"

static u8 parse_isn_input_data[32];
static u8 parse_isn_output_data[32];

QueU8 parse_isn_input = {parse_isn_input_data, parse_isn_input_data,
                         parse_isn_input_data,
                         parse_isn_input_data + sizeof(parse_isn_input_data)};
QueU8 parse_isn_output = {
    parse_isn_output_data, parse_isn_output_data, parse_isn_output_data,
    parse_isn_output_data + sizeof(parse_isn_output_data)};

X86CpuState parse_isn_cpu_state;

/* Helper for resetting processor state */
void ResetParseIsnCpuState(void)
{
   parse_isn_cpu_state.ip = 0x0000;
   parse_isn_cpu_state.cs = 0x0000;
   parse_isn_cpu_state.ds = 0x0000;
   parse_isn_cpu_state.es = 0x0000;
   parse_isn_cpu_state.ss = 0x0000;
}
