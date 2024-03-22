/*
SPDX-License-Identifier: MIT

Copyright (c) 2024 Bart Bilos
For conditions of distribution and use, see LICENSE file
*/
/**
 * \file Squantor Minunit C++ definitions
 */
#ifndef SQMINUNIT_HPP
#define SQMINUNIT_HPP

#include <iostream>
#include <list>

class UnitTest {
protected:
  UnitTest() {}

public:
  bool isTrue{true};
  static std::list<UnitTest *> testList;

  virtual ~UnitTest() {}
  virtual void runFunc() {}

  static UnitTest &getInstance() {
    static UnitTest uTest;
    return uTest;
  }

  void runTests();
};

#endif
