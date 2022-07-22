/*
SPDX-License-Identifier: MIT

Copyright (c) 2021 Bart Bilos
For conditions of distribution and use, see LICENSE file
*/
#include <board.hpp>
#include <font_8x8.h>
#include <print.h>

uint32_t ticks;

extern "C" {
void SysTick_Handler(void) {
  ticks++;
  GpioSetPortToggle(GPIO, PORT_LED, 1 << PIN_LED);
}
}

int main() {
  ticks = 0;
  uint32_t currentTicks = 0;
  boardInit();

  while (1) {
    if (currentTicks != ticks) {
      __NOP();
    }
  }
}
