/**
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2026 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 *
 * @file print_stdout.c
 * @brief Tests for stdout printing
 */
#include "log.h"
#include "stdout_stub.h"
#include <minunit.h>
#include <string.h>

static const char *output_info_line = "Hello world 123 0x541";

MINUNIT_SETUP(print_stdout_setup)
{
  log_init();
  stdout_stub_init();
  int print_count = print_stdout("Hello world %d 0x%x", 123, 0x541);
  MINUNIT_CHECK(print_count == 21);
  MINUNIT_CHECK(strcmp(stdout_stub_get(), output_info_line) == 0);
}
