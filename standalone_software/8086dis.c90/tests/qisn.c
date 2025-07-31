/*
SPDX-License-Identifier: MIT

Copyright (c) 2025 Bart Bilos
For conditions of distribution and use, see LICENSE file
*/
/*
Tests for Instruction Queue datastructure
*/
#include "minunit.h"
#include "tests.h"
#include "qisn.h"

void TestIQReset(void)
{
  QIReset();
  MinunitExpect(QIEmpty() != 0);
  MinunitExpect(QIFull() == 0);
  MinunitExpect(QILevel() == 0);
}

void TestIsnQueue(void)
{
  TestIQReset();
}