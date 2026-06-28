/**
 *
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2026 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 *
 * @file main.c
 * @brief Main entrypoint for template application
 */
#include "log.h"
#include "par_arg.h"
#include "program.h"
#include "results.h"
#include <stdio.h>
#include <string.h>

Program_state program_state;

/**
 * @brief Output string to stdout
 * @param str string to send to stdout
 */
void stdout_output(const char *str)
{ printf("%s", str); }

/**
 * @brief Output string to stdout and add newline
 * @param str string to send to stdout
 */
void stdout_output_line(const char *str)
{ printf("%s\n", str); }

/**
 * @brief main entrypoint
 * @return error code to operating system
 */
int main(int argc, char *argv[])
{
  memset(&program_state, 0, sizeof(program_state));
  Result result;
  result = parse_program_arguments(argc, argv, &program_state);
  if (result != RESULT_OK) {
    LOG_FATAL("Argument parse error");
    return 1;
  }
  result = program(&program_state);
  if (result != RESULT_OK) {
    LOG_FATAL("Program error");
    return 1;
  }
  return 0;
}
