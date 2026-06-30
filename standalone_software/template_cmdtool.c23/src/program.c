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
#include <stddef.h>

/* Application name */
const char *str_program_name = "Template commandline tool";
/* Application version */
const char *str_version = "version 0.0.0";
/* Application help */
const char *str_help = "Template program help\n"
                       "-?  Print this help\n"
                       "-v  Print version";
/* Program operation strings */
const char *str_table_prg_op[] = {"None", "Help", "Version"};

void program_set_operation(Program_state *state, Program_operation operation)
{
  if (state->operation < operation) {
    state->operation = operation;
  }
}

Result program_run(Program_state *state)
{
  LOG_DEBUG("Program operation: %s",
            str_table_prg_op[(size_t) state->operation]);
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
