/*
SPDX-License-Identifier: MIT

Copyright (c) 2026 Bart Bilos
For conditions of distribution and use, see LICENSE file
*/
/**
 * @file main.c
 * @brief Main entrypoint for template application
 */
#include "par_arg.h"
#include "program.h"
#include <memory.h>
#include <stdio.h>

Program_state program_state;

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
    printf("Argument parse error\n");
    return 1;
  }
  return 0;
}
