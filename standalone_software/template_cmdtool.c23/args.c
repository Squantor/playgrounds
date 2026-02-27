/*
SPDX-License-Identifier: MIT

Copyright (c) 2026 Bart Bilos
For conditions of distribution and use, see LICENSE file
*/
/**
 * @file args.c
 * @brief Program arguments list definitions
 */
#include "args.h"
#include <stdlib.h>

Argument_entry arguments[] = {
  { "h", "Print this help message" },
  { "v", "Print version information" },
  { NULL, NULL },
};