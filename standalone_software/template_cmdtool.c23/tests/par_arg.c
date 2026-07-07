/**
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2026 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 *
 * @file par_arg.c
 * @brief Tests for commandline argument parser
 * @todo check logging output
 * @todo check help output as par_arg generates help messages
 */
#include "par_arg.h"
#include "log.h"
#include "program.h"
#include "results.h"
#include "stdout_mock.h"
#include <minunit.h>
#include <string.h>

MINUNIT_SETUP(parse_program_setup)
{
  log_init();
  stdout_mock_init();
  MINUNIT_PASS();
}

MINUNIT_ADD(parse_program_empty, parse_program_setup, nullptr)
{
  int test_argc = 1;
  char *test_argv[] = {"test_program"};
  Program_state program_state;
  memset(&program_state, 0, sizeof(program_state));
  MINUNIT_CHECK(parse_program_arguments(&program_state, test_argc, test_argv) ==
                RESULT_ARG_PARSE_ERROR);
  MINUNIT_CHECK(program_state.operation == P_OP_NONE);
}

MINUNIT_ADD(parse_program_no_true_args, parse_program_setup, nullptr)
{
  int test_argc = 3;
  char *test_argv[] = {"test_program", "-", "-"};
  Program_state program_state = {P_OP_NONE};
  MINUNIT_CHECK(parse_program_arguments(&program_state, test_argc, test_argv) ==
                RESULT_ARG_PARSE_ERROR);
  MINUNIT_CHECK(program_state.operation == P_OP_NONE);
}

MINUNIT_ADD(parse_program_help, parse_program_setup, nullptr)
{
  int test_argc = 2;
  char *test_argv[] = {"test_program", "help"};
  Program_state program_state = {P_OP_NONE};
  MINUNIT_CHECK(parse_program_arguments(&program_state, test_argc, test_argv) ==
                RESULT_OK);
  MINUNIT_CHECK(program_state.operation == P_OP_NONE);
}

MINUNIT_ADD(parse_program_version, parse_program_setup, nullptr)
{
  int test_argc = 2;
  char *test_argv[] = {"test_program", "version"};
  Program_state program_state = {P_OP_NONE};
  MINUNIT_CHECK(parse_program_arguments(&program_state, test_argc, test_argv) ==
                RESULT_OK);
  MINUNIT_CHECK(program_state.operation == P_OP_VERSION);
}

MINUNIT_ADD(parse_program_help_version, parse_program_setup, nullptr)
{
  int test_argc = 3;
  char *test_argv[] = {"test_program", "version", "help"};
  Program_state program_state = {P_OP_NONE};
  MINUNIT_CHECK(parse_program_arguments(&program_state, test_argc, test_argv) ==
                RESULT_ARG_PARSE_ERROR);
  MINUNIT_CHECK(program_state.operation == P_OP_NONE);
}

MINUNIT_ADD(parse_program_logging, parse_program_setup, nullptr)
{
  int test_argc = 2;
  char *test_argv[] = {"test_program", "-L4"};
  Program_state program_state = {P_OP_NONE};
  MINUNIT_CHECK(parse_program_arguments(&program_state, test_argc, test_argv) ==
                RESULT_ARG_PARSE_ERROR);
  MINUNIT_CHECK(program_state.operation == P_OP_NONE);
  MINUNIT_CHECK(log_get_level() == LOGVAL_DEBUG);
}

MINUNIT_ADD(parse_program_logging_empty_error, parse_program_setup, nullptr)
{
  int test_argc = 2;
  char *test_argv[] = {"test_program", "-L"};
  Program_state program_state = {P_OP_NONE};
  MINUNIT_CHECK(parse_program_arguments(&program_state, test_argc, test_argv) ==
                RESULT_ARG_PARSE_ERROR);
  MINUNIT_CHECK(program_state.operation == P_OP_NONE);
  MINUNIT_CHECK(log_get_level() == LOGVAL_WARNING);
}

MINUNIT_ADD(parse_program_logging_invalid_error, parse_program_setup, nullptr)
{
  int test_argc = 2;
  char *test_argv[] = {"test_program", "-L9"};
  Program_state program_state = {P_OP_NONE};
  MINUNIT_CHECK(parse_program_arguments(&program_state, test_argc, test_argv) ==
                RESULT_ARG_PARSE_ERROR);
  MINUNIT_CHECK(program_state.operation == P_OP_NONE);
  MINUNIT_CHECK(log_get_level() == LOGVAL_WARNING);
}
