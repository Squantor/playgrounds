/**
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2026 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 *
 * @file log.c
 * @brief Tests for simple logger
 */
#include "log.h"
#include "stdout_mock.h"
#include <minunit.h>
#include <string.h>

static const char *output_info_line =
    "   INFO:               log.c:  35: This is a test log line\n";

MINUNIT_SETUP(log_setup)
{
  log_init();
  stdout_mock_init();
  MINUNIT_PASS();
}

MINUNIT_ADD(log_info_line_ignored, log_setup, nullptr)
{
  LOG_INFO("This is a test log line");
  const char *str_out = stdout_mock_get();
  MINUNIT_CHECK(str_out == NULL);
}

MINUNIT_ADD(log_info_line_written, log_setup, nullptr)
{
  log_set_level(LOGVAL_INFO);
  LOG_INFO("This is a test log line");
  const char *str_out = stdout_mock_get();
  MINUNIT_CHECK(strcmp(str_out, output_info_line) == 0);
}
