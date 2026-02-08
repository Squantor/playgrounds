/*
SPDX-License-Identifier: MIT

Copyright (c) 2026 Bart Bilos
For conditions of distribution and use, see LICENSE file
*/
/**
 * @file main.c
 * Main entrypoint for template application
 */
#include "par_arg.h"
#include <stdio.h>

Program_state program_state;

/**
 * @brief main entrypoint
 * @return error code to operating system
 */
int main(int argc, char *argv[])
{
  parse_program_arguments(argc, argv, &program_state);
  printf("Hello world!\n");
  return 0;
}
