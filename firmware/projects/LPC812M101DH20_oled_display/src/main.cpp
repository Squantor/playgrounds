/*
SPDX-License-Identifier: MIT

Copyright (c) 2021 Bart Bilos
For conditions of distribution and use, see LICENSE file
*/
#include <board.hpp>
#include <SSD1306_direct.hpp>
#include <graphicalconsole.hpp>
#include <font_8x8.h>
#include <print.h>

using namespace util;

uint32_t ticks;

extern "C" {
void SysTick_Handler(void) {
  ticks++;
  gpioPortToggle(GPIO, PORT_LED, 1 << PIN_LED);
}
}

SSD1306::display<0x78, SSD1306::standard128x64> currentDisplay;
graphicalConsole<SSD1306::standard128x64::maxX, SSD1306::standard128x64::maxY> currentConsole(mono8x8RowFlip);

void currentDisplayWriteWindow(uint8_t xBegin, uint8_t xEnd, uint8_t yBegin, uint8_t yEnd, const uint8_t *data, uint16_t length) {
  currentDisplay.writeWindow(xBegin, xEnd, yBegin, yEnd, data, length);
}

result currentDisplayWriteChar(const char *c) {
  currentConsole.writeBigChar(currentDisplayWriteWindow, *c);
  return noError;
}

const datastreamChar_t displayStream{
  .write = currentDisplayWriteChar,
  .read = NULL,
  .name = NULL,
};

int main() {
  ticks = 0;
  uint32_t currentTicks = 0;
  boardInit();

  currentDisplay.init();
  dsPuts(&displayStream, "Hello World!");

  while (1) {
    if (currentTicks != ticks) {
      printDecNzU32(&displayStream, currentTicks);
      dsWriteChar(&displayStream, currentTicks & 0x7F);
      currentTicks = ticks;
      uint8_t invertDisplay;
      if (currentTicks & 16)
        invertDisplay = SSD1306::displayInvert;
      else
        invertDisplay = SSD1306::displayNormal;
      currentDisplay.sendCommands(&invertDisplay, sizeof(invertDisplay));
      currentDisplay.update();
    }
  }
}
