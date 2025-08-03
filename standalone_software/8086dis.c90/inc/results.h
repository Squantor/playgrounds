/*
SPDX-License-Identifier: MIT

Copyright (c) 2025 Bart Bilos
For conditions of distribution and use, see LICENSE file
*/
/*
8086 disassembler function results
*/
#ifndef RESULTS_H
#define RESULTS_H

typedef enum {
   NO_ERROR = 0, /* No error */
   ERROR,        /* Unspecified error occured */
   BUSY,         /* Busy */
   READY,        /* Ready */
   ISN_UNKNOWN   /* Uknown instruction */
} Results;

#endif
