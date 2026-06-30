/**
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2026 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 *
 * @file par_arg.c
 * @brief Commandline argument parser
 */
#include "par_arg.h"
#include "log.h"
#include "program.h"
#include "results.h"
#include <ctype.h>
#include <stdint.h>
#include <string.h>

typedef enum {
  ARG_PARSE_IDLE,       /*< Idle state */
  ARG_PARSE_ERR,        /*< Error state */
  ARG_PARSE_DONE,       /*< Done state */
  ARG_PARSE_OPT_TOKENS, /*< Parsing option token */
  ARG_PARSE_OPT_ARG,    /*< Parsing option operator */
  ARG_PARSE_CMD,        /*< Parsing command */
} Argument_parse_state;

/**
 * @todo change some options to commands, a command is an option without a minus
 * @todo When one argument is a command other commands are an error
 * @todo There needs to be at least one command present
 * @todo When there is a command, other command shaped things could be arguments
 */
Result parse_program_arguments(Program_state *state, int argc, char *argv[])
{
  Argument_parse_state arg_parse_state = ARG_PARSE_IDLE;
  size_t cmd_index = MAX_COMMAND_HANDLERS;
  // skip first commandline argument as that is the executable name
  for (int i = 1; i < argc; i++) {
    char *p = argv[i];
    // determine what type of argument we have
    if (*p == '-') {
      arg_parse_state = ARG_PARSE_OPT_TOKENS;
      p++;
    } else if (isalpha(*p)) {
      arg_parse_state = ARG_PARSE_CMD;
    } else {
      LOG_FATAL("Cant determine argument class of \"%s\"", p);
      arg_parse_state = ARG_PARSE_ERR;
    }
    // We have some additional work to do
    if (arg_parse_state == ARG_PARSE_OPT_TOKENS) {
      // parse options
      if (*p == '?') {  // move this into a command
        program_set_operation(state, P_OP_HELP);
      } else if (*p == 'v') {  // move this into a command
        program_set_operation(state, P_OP_VERSION);
      } else if (*p == 'L') {
        p++;
        if (*p >= '0' && *p <= '5') {
          log_set_level(*p - '0');
        } else {  // add more options here
          LOG_FATAL("Unknown Logging level %c", *p);
          arg_parse_state = ARG_PARSE_ERR;
        }
      } else {
        LOG_FATAL("Unknown option -%c", *p);
        arg_parse_state = ARG_PARSE_ERR;
      }
    } else if (arg_parse_state == ARG_PARSE_CMD) {
      // parse command
      size_t j = 0;
      for (; j < MAX_COMMAND_HANDLERS; j++) {
        // loop until we find the command
        if (strcmp(command_handlers[j].pattern, p) == 0) {
          if (cmd_index == MAX_COMMAND_HANDLERS) {
            cmd_index = j;
          } else {
            LOG_FATAL("Multiple commands found");
            arg_parse_state = ARG_PARSE_ERR;
          }
          break;
        }
      }
      if (j == MAX_COMMAND_HANDLERS) {
        // argument is not a command nor an option, add it to the list
      }
    }
    if (arg_parse_state == ARG_PARSE_ERR) {
      return RESULT_ARG_PARSE_ERROR;
    }
  }
  // did we have a command?
  if (cmd_index == MAX_COMMAND_HANDLERS) {
    LOG_FATAL("No command found");
    return RESULT_ARG_PARSE_ERROR;
  }
  else
  { 
    command_handlers[cmd_index].handler(state, argc, argv);
  }
  return RESULT_OK;
}
