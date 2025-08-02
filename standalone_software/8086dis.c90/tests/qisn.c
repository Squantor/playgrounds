/*
SPDX-License-Identifier: MIT

Copyright (c) 2025 Bart Bilos
For conditions of distribution and use, see LICENSE file
*/
/*
Tests for Instruction Queue datastructure
*/
#include "qisn.h"

#include "minunit.h"
#include "tests.h"

void TestIQReset(void)
{
   QIReset();
   MinunitExpect(QIEmpty() != 0);
   MinunitExpect(QIFull() == 0);
   MinunitExpect(QILevel() == 0);
}

void TestIQPushFront(void)
{
   u8 i;
   QIReset();
   QIPushFront(0x12);
   MinunitExpect(QIEmpty() == 0);
   MinunitExpect(QILevel() == 1);
   QIPushFront(0x34);
   MinunitExpect(QIEmpty() == 0);
   MinunitExpect(QILevel() == 2);
   {
      u8 input_block[3] = {0xAB, 0xCD, 0xEF};
      QIPushFrontBlock(input_block, 3);
   }
   MinunitExpect(QIEmpty() == 0);
   MinunitExpect(QILevel() == 5);
   /* We clean out the queue so the starting position is not at the beginning
   of the array. This way we will also test wrapping */
   do {
      u8 dummy;
      QIPopBack(&dummy);
   } while (QIEmpty() == 0);
   MinunitExpect(QILevel() == 0);
   for (i = 0; i < 125; i++) {
      MinunitAssert(QILevel() == i);
      QIPushFront(i);
   }
   MinunitExpect(QIFull() == 0);
   QIPushFront(255);
   MinunitExpect(QIFull() != 0);
}

void TestIQPopBack(void)
{
   u8 i, j;
   u8 input_block[6];
   QIReset();
   for (i = 0; i < 126; i++) {
      QIPushFront(i);
   }
   MinunitExpect(QILevel() == 126);
   for (i = 0; i < 126; i++) {
      u8 element;
      QIPopBack(&element);
      MinunitAssert(element == i);
   }
   MinunitExpect(QIEmpty() != 0);
   MinunitExpect(QILevel() == 0);
   for (i = 0; i < 126; i++) {
      u8 currLevel = QILevel();
      MinunitAssert(QILevel() == i);
      QIPushFront(i);
   }
   MinunitExpect(QILevel() == 126);
   for (i = 0; i < 126; i += 6) {
      QIPopBackBlock(input_block, 6);
      for (j = 0; j < 6; j++) {
         MinunitExpect(input_block[j] == i + j);
      }
   }
   MinunitExpect(QIEmpty() != 0);
}

void TestIsnQueue(void)
{
   TestIQReset();
   TestIQPushFront();
   TestIQPopBack();
}