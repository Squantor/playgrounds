/*
SPDX-License-Identifier: MIT

Copyright (c) 2026 Bart Bilos
For conditions of distribution and use, see LICENSE file
*/
/**
 * @file results.h
 * Application wide results enum
 */
#ifndef RESULTS_H
#define RESULTS_H
#include <stdint.h>

typedef enum : uint32_t {
   RESULT_OK = 0, /*!< Success */
   RESULT_NOT_OK, /*!< Unspecified error */
} Result;

#endif