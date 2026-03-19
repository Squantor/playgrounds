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
#include "program.h"
#include "results.h"
// #include "types.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>

typedef enum {
  ARG_PARSE_IDLE,       /*< Idle state */
  ARG_PARSE_ERR,        /*< Error state */
  ARG_PARSE_DONE,       /*< Done state */
  ARG_PARSE_OPT_TOKENS, /*< Parsing option token */
  ARG_PARSE_OPT_ARG,    /*< Parsing option operator */
  ARG_PARSE_CMD,        /*< Parsing command */
} Argument_parse_state;

static Argument_parse_state arg_parse_state;

char commandline_buffer[1024];

/**
 * @todo switch from fixed buffer to an arena
 * @todo test the -v option, test -? and -v
 * @todo switch from buffer gathering to argc/argv stepping
 * @todo print/forward an error message
 */
Result parse_program_arguments(int argc, char *argv[], Program_state *state)
{
  (void) state;
  memset(commandline_buffer, 0, sizeof(commandline_buffer));
  arg_parse_state = ARG_PARSE_IDLE;
  char *p = commandline_buffer;
  char *q;  // pointer to current argv string
  // skip first commandline argument as that is the executable name
  for (int i = 1; i < argc; i++) {
    q = argv[i];
    while (*q != '\0') {
      *p = *q;
      p++;
      q++;
    }
    *p = ' ';
    p++;
    q++;
  }
  *p = '\0';
  // go through commandline buffer
  p = commandline_buffer;
  do {
    // initial tokens to check
    if (*p == '\0') {
      arg_parse_state = ARG_PARSE_DONE;
    } else if (*p == '-') {
      arg_parse_state = ARG_PARSE_OPT_TOKENS;
      p++;
      continue;
    } else if (*p == ' ') {
      arg_parse_state = ARG_PARSE_IDLE;
      p++;
      continue;
    }

    if (arg_parse_state == ARG_PARSE_OPT_TOKENS) {
      if (*p == '?') {
        state->operation = P_OP_HELP;
        arg_parse_state = ARG_PARSE_DONE;
        continue;  // help request, we are done
      } else if (*p == 'v') {
        state->operation = P_OP_VERSION;
      } else if (*p == 'L') {
        p++;
        if (*p >= '0' && *p <= '5') {
          state->log_level = (*p - '0');
        } else {
          arg_parse_state = ARG_PARSE_ERR;
          continue;
        }
      }
      p++;
    }

  } while ((arg_parse_state != ARG_PARSE_DONE) &&
           (arg_parse_state != ARG_PARSE_ERR));
  if (arg_parse_state == ARG_PARSE_ERR) {
    return RESULT_ARG_PARSE_ERROR;
  }
  return RESULT_OK;
}
