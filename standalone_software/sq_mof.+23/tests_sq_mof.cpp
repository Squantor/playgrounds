/*
SPDX-License-Identifier: MIT

Copyright (c) 2025 Bart Bilos
For conditions of distribution and use, see LICENSE file
*/
/**
 * \file tests_sq_mof.cpp
 * Unit tests for simple in place move_only_function implementation
 */

#include "minunit.h"
#include "sq_mof.hpp"
#include <string>

MINUNIT_TEARDOWN(sq_mof_teardown)
{
   MINUNIT_PASS();
}

MINUNIT_SETUP(sq_mof_setup)
{
   MINUNIT_PASS();
}

MINUNIT_ADD(sq_mof_test, sq_mof_setup, sq_mof_teardown)
{
   auto i = std::make_unique<int>(3);
   MyMoveOnlyFunction<int(int, int)> fn(
       [c = std::move(i)](int a, int b) { return a + b + *c; });
   MINUNIT_CHECK(fn(1, 2) == 6);

   MyMoveOnlyFunction<int(std::unique_ptr<int>)> pfn(
       [](auto v) { return *v + *v; });
   MINUNIT_CHECK(pfn(std::make_unique<int>(9)) == 18);
   MyMoveOnlyFunction<int(int), 40> pfn2(
       [x = std::string("0")](auto v) { return v + x[0]; });
   MINUNIT_CHECK(pfn2(3) == 51);
}