/*
SPDX-License-Identifier: MIT

Copyright (c) 2025 Bart Bilos
For conditions of distribution and use, see LICENSE file
*/

#include "minunit.h"
#include "sq_function.hpp"
#include <cstdio>
#include <functional>

uint32_t call_count;
int argument_sum;

int TestFunction(int argument)
{
   call_count++;
   argument_sum += argument;
   return argument_sum;
}

auto test_lambda = [](int argument) {
   call_count++;
   argument_sum += argument;
   return argument_sum;
};

class TestClass
{
 public:
   TestClass() = default;
   int TestFunction(int argument)
   {
      call_count++;
      argument_sum += argument;
      return argument_sum;
   }
};

TestClass test_class_instance;

MINUNIT_SETUP(FunctionTestSetup)
{
   call_count = 0;
   argument_sum = 0;
   MINUNIT_PASS();
}

MINUNIT_ADD(FunctionTestFunctionality, FunctionTestSetup, nullptr)
{
   SqFunction<int(int)> inplace_function = TestFunction;
   MINUNIT_CHECK(inplace_function(5) == 5);
   MINUNIT_CHECK(call_count == 1);
   MINUNIT_CHECK(argument_sum == 5);

   SqFunction<int(int)> inplace_lambda = test_lambda;
   MINUNIT_CHECK(inplace_lambda(10) == 15);
   MINUNIT_CHECK(call_count == 2);
   MINUNIT_CHECK(argument_sum == 15);

   /*
   SqFunction<int(TestClass &, int), 64> inplace_class_method =
       &TestClass::TestFunction;
   MINUNIT_CHECK(inplace_class_method(test_class_instance, 20) == 35);
   MINUNIT_CHECK(call_count == 3);
   MINUNIT_CHECK(argument_sum == 35);
   */

   std::function<int(TestClass &, int)> std_function_class_method =
       &TestClass::TestFunction;
   MINUNIT_CHECK(std_function_class_method(test_class_instance, 20) == 35);
   MINUNIT_CHECK(call_count == 3);
   MINUNIT_CHECK(argument_sum == 35);
}