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

static char log_line[LOG_LINE_SIZE];

static char *log_level_names[] = {"FATAL", "ERROR", "WARNING", "INFO", "DEBUG"};

static struct {
  Log_level log_level;
} Log_state;

void log_init(void)
{
  Log_state.log_level = LOGVAL_WARNING;
}

void log_set_level(Log_level log_level)
{
  Log_state.log_level = log_level;
}

Log_level log_get_level(void)
{
  return Log_state.log_level;
}

/* Overridable log output function */
__attribute__((weak)) void stdout_output(const char *)
{
}

/* Overridable log output function */
__attribute__((weak)) void stdout_output_line(const char *)
{
}

/* Write the first part of the log line to the buffer */
static int log_stamp_full(Log_level level, const char *file, int line)
{
  return snprintf(log_line, LOG_LINE_SIZE,
                  "%7s:%20s:%4d: ", log_level_names[level], file, line);
}

static int log_stamp_level(Log_level level)
{
  return snprintf(log_line, LOG_LINE_SIZE, "%s ", log_level_names[level]);
}

// NOLINTBEGIN(clang-analyzer-valist.Uninitialized)
__attribute__((format(printf, 4, 5))) void
log_log(Log_level level, const char *file, int line, const char *fmt, ...)
{
  if (level <= Log_state.log_level) {
    int stamplen = 0;
    if (Log_state.log_level > LOGVAL_INFO)
      stamplen = log_stamp_full(level, file, line);
    else
      stamplen = log_stamp_level(level);

    if ((unsigned) stamplen < LOG_LINE_SIZE) {
      va_list args;
      va_start(args, fmt);
      vsnprintf(log_line + stamplen, LOG_LINE_SIZE - stamplen, fmt, args);
      va_end(args);
      stdout_output_line(log_line);
    }
  }
}
// NOLINTEND(clang-analyzer-valist.Uninitialized)
// NOLINTBEGIN(clang-analyzer-valist.Uninitialized)
__attribute__((format(printf, 1, 2))) int print_stdout(const char *fmt, ...)
{
  va_list args;
  va_start(args, fmt);
  int ret = vsnprintf(log_line, LOG_LINE_SIZE, fmt, args);
  va_end(args);
  stdout_output(log_line);
  return ret;
}
// NOLINTEND(clang-analyzer-valist.Uninitialized)
