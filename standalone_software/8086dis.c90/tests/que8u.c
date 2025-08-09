/*
SPDX-License-Identifier: MIT

Copyright (c) 2025 Bart Bilos
For conditions of distribution and use, see LICENSE file
*/
/*
Tests for Instruction Queue datastructure
*/
#include "que8u.h"
#include "minunit.h"
#include "tests.h"
#include "types.h"

static u8 buffer[33];
static QueU8 test_queue = {buffer, buffer, buffer, buffer + sizeof(buffer)};

void TestQu8Reset(void)
{
   Qu8Reset(&test_queue);
   MinunitExpect(Qu8Empty(&test_queue) != 0);
   MinunitExpect(Qu8Full(&test_queue) == 0);
   MinunitExpect(Qu8Level(&test_queue) == 0);
}

void TestQu8PushFront(void)
{
   u8 i;
   Qu8Reset(&test_queue);
   Qu8PushFront(&test_queue, 0x12);
   MinunitExpect(Qu8Empty(&test_queue) == 0);
   MinunitExpect(Qu8Level(&test_queue) == 1);
   Qu8PushFront(&test_queue, 0x34);
   MinunitExpect(Qu8Empty(&test_queue) == 0);
   MinunitExpect(Qu8Level(&test_queue) == 2);
   {
      u8 input_block[3] = {0xAB, 0xCD, 0xEF};
      Qu8PushFrontBlock(&test_queue, input_block, 3);
   }
   MinunitExpect(Qu8Empty(&test_queue) == 0);
   MinunitExpect(Qu8Level(&test_queue) == 5);
   /* We clean out the queue so the starting position is not at the beginning
   of the array. This way we will also test wrapping */
   do {
      u8 dummy;
      Qu8PopBack(&test_queue, &dummy);
   } while (Qu8Empty(&test_queue) == 0);
   MinunitExpect(Qu8Level(&test_queue) == 0);
   for (i = 0; i < 31; i++) {
      MinunitAssert(Qu8Level(&test_queue) == i);
      Qu8PushFront(&test_queue, i);
   }
   MinunitExpect(Qu8Full(&test_queue) == 0);
   Qu8PushFront(&test_queue, 255);
   MinunitExpect(Qu8Full(&test_queue) != 0);
}

void TestQu8PopBack(void)
{
   u8 i, j;
   u8 input_block[4];
   Qu8Reset(&test_queue);
   for (i = 0; i < 32; i++) {
      Qu8PushFront(&test_queue, i);
   }
   MinunitExpect(Qu8Level(&test_queue) == 32);
   for (i = 0; i < 32; i++) {
      u8 element;
      Qu8PopBack(&test_queue, &element);
      MinunitAssert(element == i);
   }
   MinunitExpect(Qu8Empty(&test_queue) != 0);
   MinunitExpect(Qu8Level(&test_queue) == 0);
   for (i = 0; i < 32; i++) {
      MinunitAssert(Qu8Level(&test_queue) == i);
      Qu8PushFront(&test_queue, i);
   }
   MinunitExpect(Qu8Level(&test_queue) == 32);
   for (i = 0; i < 32; i += 4) {
      Qu8PopBackBlock(&test_queue, input_block, 4);
      for (j = 0; j < 4; j++) {
         MinunitExpect(input_block[j] == i + j);
      }
   }
   MinunitExpect(Qu8Empty(&test_queue) != 0);
}

void TestQu8Bidirectional(void)
{
   u8 dummy;
   Qu8Reset(&test_queue);
   Qu8PushFront(&test_queue, 0x12);
   MinunitExpect(Qu8Level(&test_queue) == 1);
   Qu8PushFront(&test_queue, 0x34);
   MinunitExpect(Qu8Level(&test_queue) == 2);
   Qu8PopBack(&test_queue, &dummy);
   MinunitExpect(Qu8Level(&test_queue) == 1);
   MinunitExpect(dummy == 0x12);
   Qu8PushBack(&test_queue, 0x56);
   MinunitExpect(Qu8Level(&test_queue) == 2);
   Qu8PushBack(&test_queue, 0x78);
   MinunitExpect(Qu8Level(&test_queue) == 3);
   Qu8PopFront(&test_queue, &dummy);
   MinunitExpect(Qu8Level(&test_queue) == 2);
   MinunitExpect(dummy == 0x34);
   Qu8PopBack(&test_queue, &dummy);
   MinunitExpect(Qu8Level(&test_queue) == 1);
   MinunitExpect(dummy == 0x78);
   Qu8PopFront(&test_queue, &dummy);
   MinunitExpect(Qu8Level(&test_queue) == 0);
   MinunitExpect(dummy == 0x56);
}

void TestQueueU8(void)
{
   TestQu8Reset();
   TestQu8PushFront();
   TestQu8PopBack();
   TestQu8Bidirectional();
}
