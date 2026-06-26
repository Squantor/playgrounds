/**
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2026 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 *
 * @file log.h
 * @brief Simple logger
 */
#ifndef LOG_H
#define LOG_H

typedef enum {
  LOG_FATAL = 0,
  LOG_ERROR = 1,
  LOG_WARNING = 2,
  LOG_INFO = 3,
  LOG_DEBUG = 4,
  LOG_NONE = 5,
} Log_level;

#define LOG_DEBUG(...) log_log(LOG_DEBUG, __FILE__, __LINE__, __VA_ARGS__)
#define LOG_INFO(...) log_log(LOG_INFO, __FILE__, __LINE__, __VA_ARGS__)
#define LOG_WARNING(...) log_log(LOG_WARNING, __FILE__, __LINE__, __VA_ARGS__)
#define LOG_ERROR(...) log_log(LOG_ERROR, __FILE__, __LINE__, __VA_ARGS__)
#define LOG_FATAL(...) log_log(LOG_FATAL, __FILE__, __LINE__, __VA_ARGS__)

void log_log(Log_level Log_level, const char *file, int line, const char *fmt,
             ...);

#endif