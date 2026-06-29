/*
SPDX-License-Identifier: MIT

Copyright (c) 2026 Bart Bilos
For conditions of distribution and use, see LICENSE file
*/
/**
 * @file program.h
 * @brief Main program declarations
 */
#ifndef PROGRAM_H
#define PROGRAM_H

#include "log.h"
#include "results.h"

typedef enum {
  P_OP_NONE = 0,    /*!< No program operation */
  P_OP_HELP = 1,    /*!< Print help */
  P_OP_VERSION = 2, /*!< Print version */
  /* Add additional program operations here */
} Program_operation;

typedef struct {
  Program_operation operation; /*!< Program operation */
} Program_state;

/**
 * @brief Set program operation
 * @param state Program state
 * @param operation Operation to execute
 */
void program_set_operation(Program_state *state, Program_operation operation);

/**
 * @brief Main program entrypoint
 * @param state Program state to execute
 * @return Result of the execution
 */
Result program_run(Program_state *state);

#endif
