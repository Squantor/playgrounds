/*
SPDX-License-Identifier: MIT

Copyright (c) 2026 Bart Bilos
For conditions of distribution and use, see LICENSE file
*/
/**
 * @file program.h
 * @brief Program wide state structure
 */
#ifndef PROGRAM_H
#define PROGRAM_H

typedef enum {
  P_OP_NONE = 0,    /*!< No program operation */
  P_OP_HELP = 1,    /*!< Print help */
  P_OP_VERSION = 2, /*!< Print version */
  /* Add additional program operations here */
} Program_operation;

typedef enum {
  LOG_FATAL = 0,
  LOG_ERROR = 1,
  LOG_WARNING = 2,
  LOG_INFO = 3,
  LOG_DEBUG = 4,
  LOG_NONE = 5,
} Log_level;

typedef struct {
  Program_operation operation; /*!< Program operation */
  Log_level log_level;         /*!< Logging level */
} Program_state;

#endif
