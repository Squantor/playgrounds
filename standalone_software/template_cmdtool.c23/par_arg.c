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

char commandline_buffer[1024];

/**
 * @todo switch from fixed buffer to an arena
 */
Result parse_program_arguments(int argc, char *argv[], Program_state *state)
{
  (void) state;
  memset(commandline_buffer, 0, sizeof(commandline_buffer));
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
  return RESULT_OK;
}
