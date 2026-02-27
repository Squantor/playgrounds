/*
SPDX-License-Identifier: MIT

Copyright (c) 2026 Bart Bilos
For conditions of distribution and use, see LICENSE file
*/
/**
 * @file par_arg.c
 * @brief Commandline argument parser
 */
#include "par_arg.h"
#include "program.h"
#include "results.h"
//#include "types.h"
#include <stdint.h>
#include <string.h>

typedef enum {
  ARG_PARSE_IDLE, /*< Idle state */
  ARG_PARSE_ERR, /*< Error state */
  ARG_PARSE_DONE, /*< Done state */
  ARG_PARSE_OPT_TOKEN, /*< Parse option token */
  ARG_PARSE_OPT_OP, /*< Parse option operator */
} Argument_parse_state;


static Argument_parse_state arg_parse_state;

char commandline_buffer[1024];

/**
 * @todo switch from fixed buffer to an arena
 */
Result parse_program_arguments(int argc, char *argv[], Program_state *state)
{
  (void) state;
  memset(commandline_buffer, 0, sizeof(commandline_buffer));
  arg_parse_state = ARG_PARSE_IDLE;
  char *p = commandline_buffer;
  char *q; // pointer to current argv string
  // skip first commandline argument as that is the executable name
  for(int i = 1; i < argc; i++) {
    q = argv[i];
    while(*q != '\0') {
      *p = *q;
      p++;
      q++;
    }
    *p = ' ';
    p++;
    q++;
  }
  // go through the commandline_buffer and parse the arguments in a big switch case statement
  do
  {
  } while ((arg_parse_state != ARG_PARSE_DONE) && (arg_parse_state != ARG_PARSE_ERR));
  
  return RESULT_OK;
}
