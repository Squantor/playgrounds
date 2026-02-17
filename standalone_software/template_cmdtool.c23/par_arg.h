/*
SPDX-License-Identifier: MIT

Copyright (c) 2026 Bart Bilos
For conditions of distribution and use, see LICENSE file
*/
/**
 * @file par_arg.h
 * Commandline argument parser definitions
 */
#ifndef PAR_ARG_H
#define PAR_ARG_H

#include "program.h"
#include "results.h"

/**
 * @brief Parse commandline arguments
 * @param argc Argument count
 * @param argv array of string pointers to arguments
 * @param state Filled in program state
 * @return Result of the parsing
 */
Result parse_program_arguments(int argc, char *argv[], Program_state *state);

#endif
