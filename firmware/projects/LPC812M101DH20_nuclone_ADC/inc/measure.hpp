/*
SPDX-License-Identifier: MIT

Copyright (c) 2023 Bart Bilos
For conditions of distribution and use, see LICENSE file
*/
/**
 * @file measurement process header definitions
 */
#ifndef MEASURE_HPP
#define MEASURE_HPP

#include <cstdint>
#include <sq_coro.hpp>
#include <systick.hpp>
#include <board.hpp>

class measure {
 public:
  measure() : currSystick{0} {};
  ~measure() = default;

  void execute(void);

 private:
  uint32_t currSystick;
  util::coroState crCurrent;
};

#endif