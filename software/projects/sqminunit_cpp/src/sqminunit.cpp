/*
SPDX-License-Identifier: MIT

Copyright (c) 2024 Bart Bilos
For conditions of distribution and use, see LICENSE file
*/
/**
 * \file Squantor Minunit C++ declarations
 */

#include <sqminunit.hpp>

void UnitTest::runTests() {
  int passed{0};
  int failed{0};

  if (testList.empty()) {
    std::cout << "No tests registered!!" << std::endl;
    return;
  }

  for (UnitTest *x : testList) {
    x->runFunc();
    x->isTrue ? ++passed : ++failed;
  }
}