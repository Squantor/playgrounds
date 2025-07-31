/*
SPDX-License-Identifier: MIT

Copyright (c) 2025 Bart Bilos
For conditions of distribution and use, see LICENSE file
*/
/*
Definitions of the instruction queue datastructure
*/
#ifndef QISN_H
#define QISN_H

#include "types.h"

#define MAX_ISN_QUEUE_SIZE  128

/*
TODO API:
QIFull
QIEmpty
QILevel
QIPushBack
QIPushBackBlock
QIPushFront
QIPushFrontBlock
QIPopBack
QIPopBackBlock
QIPopFrontBlock
QIPeekBackBlock
QIPeekFrontBlock
*/

/* Reset Instruction queue */
void QIReset(void);

/* Returns non zero if the queue is full */
int QIFull(void);

/* Returns non zero if the queue is empty */
int QIEmpty(void);

/* Returns the current queue level */
u8 QILevel();

#endif