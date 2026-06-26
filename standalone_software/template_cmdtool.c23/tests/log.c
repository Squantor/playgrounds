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
#include "stdout_stub.h"
#include <minunit.h>
#include <string.h>

static const char *output_info_line =
    "   INFO:         tests/log.c:  34: This is a test log line";

MINUNIT_SETUP(log_setup)
{
  log_init();
  stdout_stub_init();
  MINUNIT_PASS();
}

MINUNIT_ADD(log_info_line_ignored, log_setup, nullptr)
{
  LOG_INFO("This is a test log line");
  MINUNIT_CHECK(strlen(stdout_stub_get()) == 0);
}

MINUNIT_ADD(log_info_line_written, log_setup, nullptr)
{
  log_set_level(LOGVAL_INFO);
  LOG_INFO("This is a test log line");
  MINUNIT_CHECK(strcmp(stdout_stub_get(), output_info_line) == 0);
}