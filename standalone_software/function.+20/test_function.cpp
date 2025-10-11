/*
SPDX-License-Identifier: MIT

Copyright (c) 2025 Bart Bilos
For conditions of distribution and use, see LICENSE file
*/

#include "sq_function.hpp"
#include <cstdio>
#include <minunit.h>

MINUNIT_ADD(FunctionTest, nullptr, nullptr)
{
   SqFunction<void(), 100> inplace_f = []() { printf("Call from lambda\n"); };
   inplace_f();
   MINUNIT_PASS();
}