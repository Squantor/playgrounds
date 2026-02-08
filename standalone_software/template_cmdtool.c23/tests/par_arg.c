/*
SPDX-License-Identifier: MIT

Copyright (c) 2026 Bart Bilos
For conditions of distribution and use, see LICENSE file
*/
/**
 * @file par_arg.c
 * Tests for commandline argument parser
 */
#include "par_arg.h"
#include <minunit.h>

MINUNIT_SETUP(parse_program_arguments_setup)
{
  MINUNIT_PASS();
}

MINUNIT_TEARDOWN(parse_program_arguments_teardown)
{
  MINUNIT_PASS();
}

MINUNIT_ADD(parse_program_arguments, parse_program_arguments_setup,
            parse_program_arguments_teardown)
{
  MINUNIT_PASS();
}