/*
SPDX-License-Identifier: MIT

Copyright (c) 2025 Bart Bilos
For conditions of distribution and use, see LICENSE file
*/
/*
Implementation of the instruction queue datastructure
*/
#include "qisn.h"
#include "types.h"
#include <stddef.h>
#include <string.h>

static u8 data[MAX_ISN_QUEUE_SIZE];
static u8 *front;
static u8 *back;

static u8 *Increment(u8 *ptr)
{
   if ((ptr + 1) == &data[MAX_ISN_QUEUE_SIZE - 1])
      return data;
   else
      return ptr + 1;
}

static u8 *Decrement(u8 *ptr)
{
   if (ptr == data)
      return &data[MAX_ISN_QUEUE_SIZE - 1];
   else
      return ptr - 1;
}

void QIReset(void)
{
   memset(data, 0, MAX_ISN_QUEUE_SIZE);
   front = data;
   back = data;
}

int QIFull(void)
{
   return Increment(front) == back;
}

int QIEmpty(void)
{
   return (front == back);
}

u8 QILevel(void)
{
   if (front > back)
      return (u8) (front - back);
   if (back > front)
      return (u8) ((MAX_ISN_QUEUE_SIZE - 1) - (back - front));
   return 0;
}

void QIPushFront(u8 element)
{
   u8 *temp;
   if (QIFull())
      return;
   temp = Increment(front);
   *front = element;
   front = temp;
}

void QIPushFrontBlock(u8 *elements, u8 size)
{
   u8 count = size;
   do {
      if (QIFull())
         return;
      QIPushFront(*elements);
      elements++;
      count--;
   } while (count > 0);
}

void QIPopBack(u8 *element)
{
   u8 *temp;
   if (QIEmpty())
      return;
   temp = Increment(back);
   *element = *back;
   back = temp;
}

void QIPopBackBlock(u8 *elements, u8 size)
{
   u8 count = size;
   do {
      if (QIEmpty())
         return;
      QIPopBack(elements);
      elements++;
      count--;
   } while (count > 0);
}
