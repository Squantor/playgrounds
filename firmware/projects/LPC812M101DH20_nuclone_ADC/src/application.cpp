/*
SPDX-License-Identifier: MIT

Copyright (c) 2023 Bart Bilos
For conditions of distribution and use, see LICENSE file
*/
/**
 * @file executor main loop
 */
#include <board.hpp>
#include <blinky.hpp>
#include <systick.hpp>
#include <blinky.hpp>
#include <measure.hpp>

blinky appBlinky;
measure appMeasure;

void applicationLoop(void) {
  static uint32_t currentSysTick = sysTick;
  while (1) {
    appBlinky.execute();
    appMeasure.execute();
  }
}