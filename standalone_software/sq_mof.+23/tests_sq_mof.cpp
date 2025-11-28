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

int dut_function_call_count = 0;
int dut_function_value = 0;

int DutFunction(int input)
{
   int previous = dut_function_value;
   dut_function_value = input;
   dut_function_call_count++;
   return previous;
}

MINUNIT_TEARDOWN(sq_mof_teardown)
{
   MINUNIT_PASS();
}

MINUNIT_SETUP(sq_mof_setup)
{
   dut_function_call_count = 0;
   dut_function_value = 0;
   MINUNIT_PASS();
}

MINUNIT_ADD(sq_mof_constructors, sq_mof_setup, sq_mof_teardown)
{
   sq::MyMoveOnlyFunction<int(int)> mof_empty{};
   sq::MyMoveOnlyFunction<int(int)> mof_empty_with_nullptr{nullptr};
   sq::MyMoveOnlyFunction<int(int)> mof_with_function{DutFunction};
   sq::MyMoveOnlyFunction<int(int)> mof_with_lambda{[](int a) { return a; }};

   MINUNIT_CHECK(mof_empty == nullptr);
   MINUNIT_CHECK(mof_empty_with_nullptr == nullptr);
   MINUNIT_CHECK(mof_with_function != nullptr);
   MINUNIT_CHECK(mof_with_lambda != nullptr);

   sq::MyMoveOnlyFunction<int(int)> mof_with_function_move{
       std::move(mof_with_function)};
   sq::MyMoveOnlyFunction<int(int)> mof_with_lambda_move{
       std::move(mof_with_lambda)};

   MINUNIT_CHECK(mof_with_function == nullptr);
   MINUNIT_CHECK(mof_with_function_move != nullptr);
   MINUNIT_CHECK(mof_with_lambda == nullptr);
   MINUNIT_CHECK(mof_with_lambda_move != nullptr);
}

MINUNIT_ADD(sq_mof_operators, sq_mof_setup, sq_mof_teardown)
{
   sq::MyMoveOnlyFunction<int(int)> mof_with_function{DutFunction};
   MINUNIT_CHECK(mof_with_function != nullptr);
   MINUNIT_CHECK(mof_with_function(1) == 0);
   MINUNIT_CHECK(mof_with_function(2) == 1);
   MINUNIT_CHECK(dut_function_call_count == 2);
   sq::MyMoveOnlyFunction<int(int)> mof_with_function_move{};
   MINUNIT_CHECK(mof_with_function_move == nullptr);
   mof_with_function_move = std::move(mof_with_function);
   MINUNIT_CHECK(mof_with_function == nullptr);
   MINUNIT_CHECK(mof_with_function_move != nullptr);
   MINUNIT_CHECK(mof_with_function_move(3) == 2);
   MINUNIT_CHECK(mof_with_function_move(4) == 3);
   MINUNIT_CHECK(dut_function_call_count == 4);
   sq::MyMoveOnlyFunction<int(int)> mof_with_function_lambda{
       [](int a) { return a; }};
   MINUNIT_CHECK(mof_with_function_lambda != nullptr);
   MINUNIT_CHECK(mof_with_function_lambda(5) == 5);
   MINUNIT_CHECK(mof_with_function_lambda(6) == 6);
   sq::MyMoveOnlyFunction<int(int)> mof_with_function_lambda_move{};
   MINUNIT_CHECK(mof_with_function_lambda_move == nullptr);
   mof_with_function_lambda_move = std::move(mof_with_function_lambda);
   MINUNIT_CHECK(mof_with_function_lambda == nullptr);
   MINUNIT_CHECK(mof_with_function_lambda_move != nullptr);
   MINUNIT_CHECK(mof_with_function_lambda_move(7) == 7);
   MINUNIT_CHECK(mof_with_function_lambda_move(8) == 8);
}

MINUNIT_ADD(sq_mof_test, sq_mof_setup, sq_mof_teardown)
{
   auto i = std::make_unique<int>(3);
   sq::MyMoveOnlyFunction<int(int, int)> fn(
       [c = std::move(i)](int a, int b) { return a + b + *c; });
   MINUNIT_CHECK(fn(1, 2) == 6);

   sq::MyMoveOnlyFunction<int(std::unique_ptr<int>)> pfn(
       [](auto v) { return *v + *v; });
   MINUNIT_CHECK(pfn(std::make_unique<int>(9)) == 18);

   sq::MyMoveOnlyFunction<int(int), 40> pfn2(
       [x = std::string("0")](auto v) { return v + x[0]; });
   MINUNIT_CHECK(pfn2(3) == 51);
}