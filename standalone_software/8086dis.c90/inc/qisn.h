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

#define MAX_ISN_QUEUE_SIZE 128

/*
TODO API:
QIPushBack
QIPushBackBlock
QIPopFront
QIPopFrontBlock
QIPopBack
QIPopBackBlock
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

/* Put single element to the front of the queue */
void QIPushFront(u8 element);

/* Put an array of elements to the front of the queue */
void QIPushFrontBlock(u8 *elements, u8 size);

/* Remove single element from the back of the queue */
void QIPopBack(u8 *element);

/* Remove an array of elements from the back of the queue */
void QIPopBackBlock(u8 *elements, u8 size);

#endif