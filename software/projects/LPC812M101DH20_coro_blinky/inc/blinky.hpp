/*
SPDX-License-Identifier: MIT

Copyright (c) 2023 Bart Bilos
For conditions of distribution and use, see LICENSE file
*/
/**
 * @file blinky header definitions
 */
#ifndef BLINKY_HPP
#define BLINKY_HPP

#include <cstdint>
#include <sq_coro.hpp>
#include <systick.hpp>
#include <board.hpp>

class blinky {
 public:
  blinky() : currSystick{0} {};
  ~blinky() = default;

  void execute(void) {
    CR_BEGIN(crCurrent);
    CR_WAIT_V(crCurrent, currSystick != sysTick);
    currSystick = sysTick;
    gpioPeripheral.toggle(ledPin);
    CR_END_V(crCurrent);
  }

 private:
  uint32_t currSystick;
  util::coroState crCurrent;
};

#endif