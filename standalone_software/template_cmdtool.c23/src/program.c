/**
 *
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2026 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 *
 * @file program.c
 * @brief Main program definition for template application
 */
#include "program.h"
#include "log.h"
#include "results.h"

const char *str_program_name = "Template commandline tool";
const char *str_version = "version 0.0.0";
const char *str_help = "Template program help\n"
                       "-?  Print this help\n"
                       "-v  Print version";

Result program(Program_state *state)
{
  switch (state->operation) {
  case P_OP_NONE:
    print_stdout("%s %s\n", str_program_name, str_version);
    break;
  case P_OP_VERSION:
    print_stdout("%s\n", str_version);
    break;
  case P_OP_HELP:
    print_stdout("%s\n", str_help);
    break;
  default:
    break;
  }
  return RESULT_OK;
}
