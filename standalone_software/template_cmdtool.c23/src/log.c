/**
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2026 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 *
 * @file log.c
 * @brief Simple logger
 */
#include "log.h"
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

static char log_line[LOG_LINE_SIZE];

static char *log_level_names[] = {"FATAL", "ERROR", "WARNING", "INFO", "DEBUG"};

static struct {
  Log_level log_level;
} Log_state;

void log_init(void)
{
  Log_state.log_level = LOG_WARNING;
}

void log_set_level(Log_level Log_level)
{
  Log_state.log_level = Log_level;
}

/* Overridable log output function */
__attribute__((weak)) void stdout_output(const char *)
{
}

/* Write the first part of the log line to the buffer */
static int log_stamp(Log_level level, const char *file, int line)
{
  return snprintf(log_line, LOG_LINE_SIZE,
                  "%7s:%20s:%4d: ", log_level_names[level], file, line);
}

void log_log(Log_level level, const char *file, int line, const char *fmt, ...)
{
  if (level <= Log_state.log_level) {
    int stamplen = log_stamp(level, file, line);
    if (stamplen > 0) {
      va_list args;
      va_start(args, fmt);
      vsnprintf(log_line + stamplen, sizeof(log_line) - stamplen, fmt, args);
      va_end(args);
      stdout_output(log_line);
    }
  }
}

int print_stdout(const char *fmt, ...)
{
  va_list args;
  va_start(args, fmt);
  int ret = vsnprintf(log_line, sizeof(log_line), fmt, args);
  va_end(args);
  stdout_output(log_line);
  return ret;
}
