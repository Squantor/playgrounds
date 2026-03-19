/*
SPDX-License-Identifier: MIT

Copyright (c) 2026 Bart Bilos
For conditions of distribution and use, see LICENSE file
*/
/**
 * @file par_arg.c
 * @brief Tests for commandline argument parser
 * @todo test logging on with no level should error
 * @todo test logging on with invalid level should error
 * @todo test command which is an option without a minus in front
 */
#include "par_arg.h"
#include <memory.h>
#include <minunit.h>

MINUNIT_ADD(parse_program_empty, nullptr, nullptr)
{
  int test_argc = 1;
  char *test_argv[] = {"test_program"};
  Program_state program_state;
  memset(&program_state, 0, sizeof(program_state));
  MINUNIT_CHECK(parse_program_arguments(test_argc, test_argv, &program_state) ==
                RESULT_OK);
  MINUNIT_CHECK(program_state.operation == P_OP_NONE);
}

MINUNIT_ADD(parse_program_no_true_args, nullptr, nullptr)
{
  int test_argc = 3;
  char *test_argv[] = {"test_program", "-", "-"};
  Program_state program_state = {P_OP_NONE};
  MINUNIT_CHECK(parse_program_arguments(test_argc, test_argv, &program_state) ==
                RESULT_OK);
  MINUNIT_CHECK(program_state.operation == P_OP_NONE);
}

MINUNIT_ADD(parse_program_help, nullptr, nullptr)
{
  int test_argc = 2;
  char *test_argv[] = {"test_program", "-?"};
  Program_state program_state = {P_OP_NONE};
  MINUNIT_CHECK(parse_program_arguments(test_argc, test_argv, &program_state) ==
                RESULT_OK);
  MINUNIT_CHECK(program_state.operation == P_OP_HELP);
}

MINUNIT_ADD(parse_program_version, nullptr, nullptr)
{
  int test_argc = 2;
  char *test_argv[] = {"test_program", "-v"};
  Program_state program_state = {P_OP_NONE};
  MINUNIT_CHECK(parse_program_arguments(test_argc, test_argv, &program_state) ==
                RESULT_OK);
  MINUNIT_CHECK(program_state.operation == P_OP_VERSION);
}

MINUNIT_ADD(parse_program_help_version, nullptr, nullptr)
{
  int test_argc = 3;
  char *test_argv[] = {"test_program", "-v", "-?"};
  Program_state program_state = {P_OP_NONE};
  MINUNIT_CHECK(parse_program_arguments(test_argc, test_argv, &program_state) ==
                RESULT_OK);
  MINUNIT_CHECK(program_state.operation == P_OP_HELP);
}

MINUNIT_ADD(parse_program_logging, nullptr, nullptr)
{
  int test_argc = 2;
  char *test_argv[] = {"test_program", "-L2"};
  Program_state program_state = {P_OP_NONE};
  MINUNIT_CHECK(parse_program_arguments(test_argc, test_argv, &program_state) ==
                RESULT_OK);
  MINUNIT_CHECK(program_state.operation == P_OP_NONE);
  MINUNIT_CHECK(program_state.log_level == LOG_WARNING);
}

MINUNIT_ADD(parse_program_logging_empty_error, nullptr, nullptr)
{
  int test_argc = 2;
  char *test_argv[] = {"test_program", "-L"};
  Program_state program_state = {P_OP_NONE};
  MINUNIT_CHECK(parse_program_arguments(test_argc, test_argv, &program_state) ==
                RESULT_ARG_PARSE_ERROR);
  MINUNIT_CHECK(program_state.operation == P_OP_NONE);
  MINUNIT_CHECK(program_state.log_level == LOG_FATAL);
}

MINUNIT_ADD(parse_program_logging_invalid_error, nullptr, nullptr)
{
  int test_argc = 2;
  char *test_argv[] = {"test_program", "-L9"};
  Program_state program_state = {P_OP_NONE};
  MINUNIT_CHECK(parse_program_arguments(test_argc, test_argv, &program_state) ==
                RESULT_ARG_PARSE_ERROR);
  MINUNIT_CHECK(program_state.operation == P_OP_NONE);
  MINUNIT_CHECK(program_state.log_level == LOG_FATAL);
}