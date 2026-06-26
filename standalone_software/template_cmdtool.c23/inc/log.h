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

/* Logging line size */
#define LOG_LINE_SIZE (256u)
/* Logging levels */
typedef enum {
  LOGVAL_FATAL = 0,
  LOGVAL_ERROR = 1,
  LOGVAL_WARNING = 2,
  LOGVAL_INFO = 3,
  LOGVAL_DEBUG = 4,
  LOGVAL_NONE = 5,
} Log_level;
/* Log a message */
#define LOG_DEBUG(...) log_log(LOGVAL_DEBUG, __FILE__, __LINE__, __VA_ARGS__)
#define LOG_INFO(...) log_log(LOGVAL_INFO, __FILE__, __LINE__, __VA_ARGS__)
#define LOG_WARNING(...) \
  log_log(LOGVAL_WARNING, __FILE__, __LINE__, __VA_ARGS__)
#define LOG_ERROR(...) log_log(LOGVAL_ERROR, __FILE__, __LINE__, __VA_ARGS__)
#define LOG_FATAL(...) log_log(LOGVAL_FATAL, __FILE__, __LINE__, __VA_ARGS__)
/* Log a message */
void log_log(Log_level Log_level, const char *file, int line, const char *fmt,
             ...) __attribute__((format(printf, 4, 5)));
/* Initialize the logger */
void log_init(void);
/* Set the logging level */
void log_set_level(Log_level Log_level);
/* Get the logging level */
Log_level log_get_level(void);
/* Print a message to stdout */
int print_stdout(const char *fmt, ...) __attribute__((format(printf, 1, 2)));

#endif