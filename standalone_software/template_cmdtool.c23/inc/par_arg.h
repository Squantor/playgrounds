/**
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2026 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 *
 * @file par_arg.h
 * @brief Commandline argument parser declarations
 */
#ifndef PAR_ARG_H
#define PAR_ARG_H

#include "program.h"
#include "results.h"
#include <stddef.h>

#define MAX_COMMAND_HANDLERS 3u
#define MAX_COMMAND_ARGS 8u

/**
 * @brief Commandline argument entry
 */
typedef struct {
  char *pattern; /*!< Argument patterns */
  char *help;    /*!< Help string */
  Result (*handler)(Program_state *state, size_t argc,
                    char *argv[]); /*!< Handler */
} Argument_command;

/**
 * @brief Parse commandline arguments
 * @param argc Argument count
 * @param argv array of string pointers to arguments
 * @param state Filled in program state
 * @return Result of the parsing
 */
Result parse_program_arguments(Program_state *state, int argc, char *argv[]);

/**
 * @brief Commandline argument handlers
 */
extern Argument_command command_handlers[];

#endif
