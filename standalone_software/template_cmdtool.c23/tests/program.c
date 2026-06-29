/**
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2026 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 *
 * @file program.c
 * @brief Tests for program execution
 */
#include "program.h"
#include "log.h"
#include "stdout_mock.h"
#include <minunit.h>
#include <stdio.h>
#include <string.h>

const char *str_none_test = "Template commandline tool version 0.0.0\n";
const char *str_help_test = "Template program help\n"
                            "-?  Print this help\n"
                            "-v  Print version\n";

MINUNIT_SETUP(program_setup)
{
  log_init();
  stdout_mock_init();
  MINUNIT_PASS();
}

MINUNIT_ADD(program_empty, program_setup, nullptr)
{
  Program_state state;
  state.operation = P_OP_NONE;
  Result result = program(&state);
  MINUNIT_CHECK(result == RESULT_OK);
  const char *str_out = stdout_mock_get();
  MINUNIT_ASSERT(strlen(str_out) == 40);
  MINUNIT_CHECK(strncmp(str_out, str_none_test, strlen(str_out)) == 0);
}

MINUNIT_ADD(program_version, program_setup, nullptr)
{
  Program_state state;
  state.operation = P_OP_VERSION;
  Result result = program(&state);
  MINUNIT_CHECK(result == RESULT_OK);
  const char *str_out = stdout_mock_get();
  MINUNIT_ASSERT(strlen(str_out) == 14);
  MINUNIT_CHECK(strncmp(str_out, "version 0.0.0\n", strlen(str_out)) == 0);
}

MINUNIT_ADD(program_help, program_setup, nullptr)
{
  Program_state state;
  state.operation = P_OP_HELP;
  Result result = program(&state);
  MINUNIT_CHECK(result == RESULT_OK);
  const char *str_out = stdout_mock_get();
  MINUNIT_ASSERT(strlen(str_out) == 60);
  MINUNIT_CHECK(strncmp(str_out, str_help_test, strlen(str_out)) == 0);
}

//! @todo Make a test for log levels and no action, requires stdout stub that
//! holds more then a single string
