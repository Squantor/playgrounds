/*
SPDX-License-Identifier: MIT

Copyright (c) 2021 Bart Bilos
For conditions of distribution and use, see LICENSE file
*/
#include <array>
#include <board.hpp>

uint32_t ticks;

extern "C" {
void SysTick_Handler(void) {
  ticks++;
}
}

int main() {
  ticks = 0;
  uint32_t currentTicks = 0;
  boardInit();

  while (1) {
    if (currentTicks != ticks) {
      currentTicks = ticks;
      std::array<uint16_t, 1> dataIn{static_cast<uint16_t>(currentTicks)};
      std::array<uint16_t, 1> dataOut{0};
      spiPeripheral.transceive(instances::spi::chipEnables::SSEL, dataIn, dataOut, 16, true);
      __NOP();
    }
  }
}
