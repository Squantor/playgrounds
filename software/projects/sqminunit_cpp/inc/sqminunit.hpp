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

#include <array>
#include <cstdint>

namespace minunit {

struct test {
  test(){
      // TODO register the instantiated test at a central location
  };
  virtual void run() = 0;

private:
};

} // namespace minunit

#endif
