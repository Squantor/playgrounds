/**
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2026 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 *
 * @file log.c
 * @brief Simple logger
 *
 */
#include "log.h"

static struct {
  Log_level log_level;
} Log_state;

void log_set_level(Log_level Log_level)
{
  Log_state.log_level = Log_level;
}

// overridable function for writing log output
__attribute__((weak)) void log_output(const char *)
{
  // empty body, as this is a weak function, no action should be taken
}

// function for setting the current log level
// defining weak log outputter string

void log_log(Log_level Log_level, const char *file, int line, const char *fmt,
             ...)
{
  (void) file;
  (void) line;
  (void) fmt;
  if (Log_level < Log_state.log_level) {}
}