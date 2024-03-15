/*
SPDX-License-Identifier: MIT

Copyright (c) 2023 Bart Bilos
For conditions of distribution and use, see LICENSE file
*/
#include <board.hpp>

extern "C" {
void SysTick_Handler(void) {
  gpioPeripheral.toggle(ledPin);
}
}

int main() {
  boardInit();
  while (1) {
    __NOP();
  }
}
