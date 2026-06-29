/**
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2026 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 *
 * @file stdout.c
 * @brief Tests for stdout mock
 * @todo test with multiple strings enqueued
 */
#include "stdout_mock.h"
#include <minunit.h>
#include <stdio.h>
#include <string.h>

MINUNIT_SETUP(stdout_setup)
{
  stdout_mock_init();
  MINUNIT_PASS();
}

MINUNIT_ADD(stdout_init, stdout_setup, nullptr)
{
  MINUNIT_CHECK(stdout_mock_get() == NULL);
}

MINUNIT_ADD(stdout_insert_single_string, stdout_setup, nullptr)
{
  stdout_output("Hello world");
  const char *str_out = stdout_mock_get();
  MINUNIT_CHECK(str_out != NULL);
  MINUNIT_CHECK(strcmp(str_out, "Hello world") == 0);
}

MINUNIT_ADD(stdout_line_insert_single_string, stdout_setup, nullptr)
{
  stdout_output_line("Hello world");
  const char *str_out = stdout_mock_get();
  MINUNIT_CHECK(str_out != NULL);
  MINUNIT_CHECK(strcmp(str_out, "Hello world\n") == 0);
}

MINUNIT_ADD(stdout_insert_multi_string, stdout_setup, nullptr)
{
  stdout_output("Hello ");
  stdout_output_line("world");
  const char *str_out = stdout_mock_get();
  MINUNIT_CHECK(str_out != NULL);
  MINUNIT_CHECK(strcmp(str_out, "Hello ") == 0);
  str_out = stdout_mock_get();
  MINUNIT_CHECK(str_out != NULL);
  MINUNIT_CHECK(strcmp(str_out, "world\n") == 0);
}