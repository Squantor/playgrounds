/*
SPDX-License-Identifier: MIT

Copyright (c) 2025 Bart Bilos
For conditions of distribution and use, see LICENSE file
*/
/*
Implementation of the 8u queue
*/
#ifndef QUE8U_H
#define QUE8U_H

#include "types.h"

typedef struct {
   u8 *data;  /* Data storage of the queue */
   u8 *front; /* First element of the queue */
   u8 *back;  /* Last element of the queue */
   u8 *end;   /* Last element of data storage */
} QueU8;

/*
TODO API:
Qu8PushBack
Qu8PushBackBlock
Qu8PopFront
Qu8PopFrontBlock
Qu8PeekBackBlock
Qu8PeekFrontBlock
*/

/* Reset queue */
void Qu8Reset(QueU8 *const this);

/* Returns non zero if the queue is full */
int Qu8Full(QueU8 *const this);

/* Returns non zero if the queue is empty */
int Qu8Empty(QueU8 *const this);

/* Returns the current queue level */
u16 Qu8Level(QueU8 *const this);

/* Put single element to the front of the queue */
void Qu8PushFront(QueU8 *const this, u8 element);

/* Put single element to the back of the queue */
void Qu8PushBack(QueU8 *const this, u8 element);

/* Put an array of elements to the front of the queue */
void Qu8PushFrontBlock(QueU8 *const this, u8 *elements, u8 size);

/* Remove single element from the back of the queue */
void Qu8PopBack(QueU8 *const this, u8 *element);

/* Discard single element from the back of the queue */
void Qu8DropBack(QueU8 *const this);

/* Remove an array of elements from the back of the queue */
void Qu8PopBackBlock(QueU8 *const this, u8 *elements, u8 size);

/* Remove single element from the front of the queue */
void Qu8PopFront(QueU8 *const this, u8 *element);

/* Return back element but do not remove */
void Qu8PeekBack(QueU8 *const this, u8 *element);

/* Return back elements but do not remove */
void Qu8PeekBackBlock(QueU8 *const this, u8 *elements, u8 size);

#endif
