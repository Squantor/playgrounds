/*
SPDX-License-Identifier: MIT

Copyright (c) 2025 Bart Bilos
For conditions of distribution and use, see LICENSE file
*/
/**
 * \file tests_sq_mof.cpp
 * Unit tests for simple in place move_only_function implementation
 */

#include "asyncll.hpp"
#include "minunit.h"

AsyncLL dut_ll;

MINUNIT_TEARDOWN(callback_teardown)
{
   MINUNIT_PASS();
}

MINUNIT_SETUP(callback_setup)
{
   MINUNIT_PASS();
}

MINUNIT_ADD(callback_test, callback_setup, callback_teardown)
{
   std::size_t count = 0;
   auto callback = [&count]() { count++; };
   dut_ll.SetCallback(callback);
   dut_ll.Progress();
   MINUNIT_CHECK(count == 1);
   MINUNIT_PASS();
}