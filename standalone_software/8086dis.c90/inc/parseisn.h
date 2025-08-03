/*
SPDX-License-Identifier: MIT

Copyright (c) 2025 Bart Bilos
For conditions of distribution and use, see LICENSE file
*/
/*
Instruction parser definitions
*/
#ifndef PARSEISN_H
#define PARSEISN_H

#include "results.h"
#include "types.h"

/* Parse instructions from data array with data_size
When instruction is succesfully parsed, new_index will be updated
Result READY when instruction was parsed succesfully and ready for next one
Result ISN_UNKNOWN when instruction is invalid */
Results ParseInstruction(u8 *data, u8 data_size, u8 *new_index);

#endif
