/**
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2026 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 *
 * @file log_out_stub.c
 * @brief Log output stub definition used for unittests
 */
#include "stdout_stub.h"
#include "log.h"
#include <string.h>

static char log_line_stub_buffer[LOG_LINE_SIZE];

void stdout_stub_init(void)
{
  memset(log_line_stub_buffer, 0, sizeof(log_line_stub_buffer));
}

void stdout_output(const char *str)
{
  memcpy(log_line_stub_buffer, str, strlen(str));
}

char *stdout_stub_get(void)
{
  return log_line_stub_buffer;
}
