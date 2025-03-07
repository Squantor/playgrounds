/*
SPDX-License-Identifier: MIT

Copyright (c) 2025 Bart Bilos
For conditions of distribution and use, see LICENSE file
*/
/*
Program wide result type
*/

#ifndef SQRESULT_H
#define SQRESULT_H

typedef enum
{
  kResOk = 0,    /* No error */
  kResError = 1, /* Generic Error */
  kUnknOpt = 2,  /* Unknown option */
  kUnknCmd = 3,  /* Unknown command */
} results;

#endif