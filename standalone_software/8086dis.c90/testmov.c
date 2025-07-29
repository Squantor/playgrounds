/*
SPDX-License-Identifier: MIT

Copyright (c) 2025 Bart Bilos
For conditions of distribution and use, see LICENSE file
*/
/*
Tests for MOV instructions
*/
#include "minunit.h"
#include "tests.h"

void Test(void)
{
  MinunitExpect(1 == 1);
  MinunitExpect(1 == 2);
  MinunitAssert(1 == 1);
  MinunitAssert(1 == 2);
  MinunitExpect(1 == 3); /* should not be reached */
}

void TestMovDisassembly(void)
{
  Test();
}