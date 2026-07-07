/**
 *
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2026 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 *
 * @file program.c
 * @brief Main program definition for template application
 * @todo Make operation for copying a file, requires two non command arguments
 * @todo Make operation for moving a file
 * @todo Make operation for deleting a file
 * @todo make operation for xoring a file with an value
 */
#include "program.h"
#include "log.h"
#include "results.h"
#include <stddef.h>

/* Application name */
const char *str_program_name = "Template commandline tool";
/* Application version */
const char *str_version = "version 0.0.0";
/* Program operation strings, needs to match Program_operation enum */
const char *str_table_prg_op[] = {"None", "Version", "Copy"};

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
    break;
  case P_OP_VERSION:
    print_stdout("%s\n", str_version);
    break;
  default:
    break;
  }
  return RESULT_OK;
}
