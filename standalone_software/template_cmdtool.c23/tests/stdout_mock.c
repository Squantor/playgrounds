/**
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2026 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 *
 * @file log_out_mock.c
 * @brief Std output mock definitions used for unittests
 */
#include "stdout_mock.h"
#include "log.h"
#include <stdint.h>
#include <string.h>

static char log_line_mock_buffer[STDOUT_MOCK_BUFFER_SIZE];
static size_t log_line_head = 0;
static size_t log_line_tail = 0;

void stdout_mock_init(void)
{
  memset(log_line_mock_buffer, 0, sizeof(log_line_mock_buffer));
  log_line_head = log_line_tail = 0;
}

void stdout_output(const char *str)
{
  while (*str != '\0') {
    log_line_mock_buffer[log_line_head++] = *str;
    str++;
  }
  log_line_mock_buffer[log_line_head++] = '\0';
}

void stdout_output_line(const char *str)
{
  while (*str != '\0') {
    log_line_mock_buffer[log_line_head++] = *str;
    str++;
  }
  log_line_mock_buffer[log_line_head++] = '\n';
  log_line_mock_buffer[log_line_head++] = '\0';
}

const char *stdout_mock_get(void)
{
  const char *str_return;
  if (log_line_head == log_line_tail) {
    return NULL;
  }
  str_return = log_line_mock_buffer + log_line_tail;
  while (log_line_mock_buffer[log_line_tail++] != '\0')
    ;

  return str_return;
}
