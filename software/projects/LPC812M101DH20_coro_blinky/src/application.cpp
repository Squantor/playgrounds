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

extern "C" {
void SysTick_Handler(void) {
  gpioPeripheral.toggle(ledPin);
}
}

void applicationLoop(void) {
  while (1) {
    __WFI();
  }
}