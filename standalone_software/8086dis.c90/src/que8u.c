/*
SPDX-License-Identifier: MIT

Copyright (c) 2025 Bart Bilos
For conditions of distribution and use, see LICENSE file
*/
/*
Implementation of the 8u queue
*/
#include "que8u.h"
#include "types.h"
#include <stddef.h>

static u8 *Qu8Increment(QueU8 *const this, u8 *ptr)
{
   if ((ptr + 1) == this->end)
      return this->data;
   else
      return ptr + 1;
}

static u8 *Qu8Decrement(QueU8 *const this, u8 *ptr)
{
   if (ptr == this->data)
      return this->end - 1;
   else
      return ptr - 1;
}

void Qu8Reset(QueU8 *const this)
{
   this->front = this->data;
   this->back = this->data;
}

int Qu8Full(QueU8 *const this)
{
   return Qu8Increment(this, this->front) == this->back;
}

int Qu8Empty(QueU8 *const this)
{
   return (this->front == this->back);
}

u16 Qu8Level(QueU8 *const this)
{
   if (this->front > this->back)
      return (u16) (this->front - this->back);
   if (this->back > this->front)
      return (u16) ((this->end - this->data) + (this->front - this->back));
   return 0;
}

void Qu8PushFront(QueU8 *const this, u8 element)
{
   u8 *temp;
   if (Qu8Full(this))
      return;
   temp = Qu8Increment(this, this->front);
   *this->front = element;
   this->front = temp;
}

void Qu8PushBack(QueU8 *const this, u8 element)
{
   if (Qu8Full(this))
      return;
   this->back = Qu8Decrement(this, this->back);
   *this->back = element;
}

void Qu8PopBack(QueU8 *const this, u8 *element)
{
   u8 *temp;
   if (Qu8Empty(this))
      return;
   temp = Qu8Increment(this, this->back);
   *element = *this->back;
   this->back = temp;
}

void Qu8PopFront(QueU8 *const this, u8 *element)
{
   if (Qu8Empty(this))
      return;
   this->front = Qu8Decrement(this, this->front);
   *element = *this->front;
}

void Qu8PushFrontBlock(QueU8 *const this, u8 *elements, u8 size)
{
   u8 count = size;
   do {
      if (Qu8Full(this))
         return;
      Qu8PushFront(this, *elements);
      elements++;
      count--;
   } while (count > 0);
}

void Qu8PopBackBlock(QueU8 *const this, u8 *elements, u8 size)
{
   u8 count = size;
   do {
      if (Qu8Empty(this))
         return;
      Qu8PopBack(this, elements);
      elements++;
      count--;
   } while (count > 0);
}
