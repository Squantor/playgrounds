/**
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2026 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 *
 * @file arg_cmd.c
 * @brief Commandline command argument definitions
 */
#include "log.h"
#include "par_arg.h"
#include "program.h"
#include "results.h"
#include <stddef.h>

/* Application help */
static const char *str_help =
    "Template program options:\n"
    "-L? Where ? is between 0 and 5, 0 is fatal errors, 4 debug level.\n"
    "Template program commands:\n";

Result arg_cmd_help(Program_state *state, size_t argc, char *argv[]);
Result arg_cmd_version(Program_state *state, size_t argc, char *argv[]);
Result arg_cmd_copy(Program_state *state, size_t argc, char *argv[]);

Argument_command command_handlers[MAX_COMMAND_HANDLERS] = {
    {"help", "Prints out this help", arg_cmd_help},
    {"version", "Prints out the version", arg_cmd_version},
    {"copy", "Copy a file", arg_cmd_copy},
};

Result arg_cmd_help(Program_state *state, size_t argc, char *argv[])
{
  (void) state;
  (void) argc;
  (void) argv;
  print_stdout("%s", str_help);
  for (size_t i = 0; i < MAX_COMMAND_HANDLERS; i++) {
    print_stdout("%10s : %s\n", command_handlers[i].pattern,
                 command_handlers[i].help);
  }
  return RESULT_OK;
}

Result arg_cmd_version(Program_state *state, size_t argc, char *argv[])
{
  (void) argc;
  (void) argv;
  program_set_operation(state, P_OP_VERSION);
  return RESULT_OK;
}

Result arg_cmd_copy(Program_state *state, size_t argc, char *argv[])
{
  if (argc != 2) {
    LOG_ERROR("Copy command expects two arguments");
    return RESULT_ARG_PARSE_ERROR;
  }
  program_set_operation(state, P_OP_COPY);
  LOG_INFO("Copying %s to %s", argv[0], argv[1]);
  return RESULT_OK;
}