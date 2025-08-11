/*
SPDX-License-Identifier: MIT

Copyright (c) 2025 Bart Bilos
For conditions of distribution and use, see LICENSE file
*/
/*
Mocks and helper functions declarations
*/
#ifndef MOCKS_H
#define MOCKS_H
#include "que8u.h"
#include "x86cpu.h"

/* Reset processor state */
void ResetParseIsnCpuState(void);

/* Input instruction queue */
extern QueU8 parse_isn_input;
/* output instruction token queue */
extern QueU8 parse_isn_output;
/* processor state */
extern X86CpuState parse_isn_cpu_state;

#endif
