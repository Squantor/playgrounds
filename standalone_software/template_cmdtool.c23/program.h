/*
SPDX-License-Identifier: MIT

Copyright (c) 2026 Bart Bilos
For conditions of distribution and use, see LICENSE file
*/
/**
 * @file program.h
 * Application wide state structure
 */
#ifndef PROGRAM_H
#define PROGRAM_H

typedef enum {
  P_OP_NONE = 0,    /*!< No program operation */
  P_OP_HELP = 1,    /*!< Print help */
  P_OP_VERSION = 2, /*!< Print version */
  /* Add additional program operations here */
} Program_operation;

typedef struct {
  Program_operation operation; /*!< Program operation */
} Program_state;

#endif