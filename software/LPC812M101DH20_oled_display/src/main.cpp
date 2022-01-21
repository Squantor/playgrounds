/*
SPDX-License-Identifier: MIT

Copyright (c) 2021 Bart Bilos
For conditions of distribution and use, see LICENSE file
*/
#include <board.hpp>
#include <SSD1306.hpp>
#include <font_8x8.h>

using namespace util;

uint32_t ticks;

extern "C" {
void SysTick_Handler(void) {
  ticks++;
  GpioSetPortToggle(GPIO, PORT_LED, 1 << PIN_LED);
}
}

SSD1306::display<0x78> currentDisplay;

int main() {
  ticks = 0;
  uint32_t currentTicks = 0;
  boardInit();

  currentDisplay.init(SSD1306::init128x64, sizeof(SSD1306::init128x64));

  currentDisplay.writeWindow(0, 7, 0, 0, ascii2Font8x8(font8x8VerticalFlipped, 'h'), 8);
  currentDisplay.writeWindow(8, 15, 0, 0, ascii2Font8x8(font8x8VerticalFlipped, 'e'), 8);
  currentDisplay.writeWindow(16, 23, 0, 0, ascii2Font8x8(font8x8VerticalFlipped, 'l'), 8);
  currentDisplay.writeWindow(24, 31, 0, 0, ascii2Font8x8(font8x8VerticalFlipped, 'l'), 8);
  currentDisplay.writeWindow(32, 39, 0, 0, ascii2Font8x8(font8x8VerticalFlipped, 'o'), 8);

  while (1) {
    if (currentTicks != ticks) {
      currentTicks = ticks;
      uint8_t invertDisplay;
      if (currentTicks & 2)
        invertDisplay = SSD1306::displayInvert;
      else
        invertDisplay = SSD1306::displayNormal;
      currentDisplay.sendCommands(&invertDisplay, sizeof(invertDisplay));
    }
  }
}
