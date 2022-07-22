/*
SPDX-License-Identifier: MIT

Copyright (c) 2022 Bart Bilos
For conditions of distribution and use, see LICENSE file
*/
#include <board.hpp>

volatile int var;

extern "C" {
void SysTick_Handler(void) {
  var = var ^ 0x55;
}
}

int main() {
  boardInit();
  while (1) {
    __WFI();
  }
}
