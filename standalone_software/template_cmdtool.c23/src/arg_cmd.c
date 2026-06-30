/**
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2026 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 *
 * @file arg_cmd.c
 * @brief Commandline command argument definitions
 */
#include "par_arg.h"
#include "program.h"
#include "results.h"
#include <stddef.h>

Result arg_cmd_help(Program_state *state, int argc, char *argv[]);
Result arg_cmd_version(Program_state *state, int argc, char *argv[]);

Argument_command command_handlers[MAX_COMMAND_HANDLERS] = {
    {"help", "Prints out this help", arg_cmd_help},
    {"version", "Prints out the version", arg_cmd_version},
};

Result arg_cmd_help(Program_state *state, int argc, char *argv[])
{
  (void) state;
  (void) argc;
  (void) argv;
  program_set_operation(state, P_OP_HELP);
  return RESULT_OK;
}

Result arg_cmd_version(Program_state *state, int argc, char *argv[])
{
  (void) state;
  (void) argc;
  (void) argv;
  program_set_operation(state, P_OP_VERSION);
  return RESULT_OK;
}