/*
SPDX-License-Identifier: MIT

Copyright (c) 2021 Bart Bilos
For conditions of distribution and use, see LICENSE file
*/
#include <board.hpp>

uint32_t ticks;

extern "C" {
void SysTick_Handler(void) {
  ticks++;
  ledState(ticks & 0x1);
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
