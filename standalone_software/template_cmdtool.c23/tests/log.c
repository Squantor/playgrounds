/**
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2026 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 *
 * @file par_arg.c
 * @brief Tests for commandline argument parser
 * @todo test logging on with no level should error
 * @todo test logging on with invalid level should error
 * @todo test command which is an option without a minus in front
 */
#include "log.h"
#include "log_out_stub.h"
#include <minunit.h>
#include <string.h>

static const char *output_info_line =
    "   INFO:         tests/log.c:  37: This is a test log line";

MINUNIT_SETUP(log_setup)
{
  log_init();
  log_out_stub_init();
  MINUNIT_PASS();
}

MINUNIT_ADD(log_info_line_ignored, log_setup, nullptr)
{
  LOG_INFO("This is a test log line");
  MINUNIT_CHECK(strlen(log_out_stub_get()) == 0);
}

MINUNIT_ADD(log_info_line_written, log_setup, nullptr)
{
  log_set_level(LOG_INFO);
  LOG_INFO("This is a test log line");
  MINUNIT_CHECK(strcmp(log_out_stub_get(), output_info_line) == 0);
}