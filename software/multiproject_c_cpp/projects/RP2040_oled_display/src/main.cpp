/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2023 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/*
 * This is simple example file which does do any I/O and thus
 * can be compiled and run on any Cortex-M MCU. However, to see
 * its effect, you'll need to use debugger.
 */
#include <nuclone_RP2040.hpp>
#include <SSD1306_direct.hpp>
#include <graphicalconsole.hpp>
#include <font_8x8.h>
#include <print.h>

volatile uint32_t systicks = 0;
const uint8_t helloString[] = "Hello World\n";

extern "C" {
void SysTick_Handler(void) {
  systicks = systicks + 1;
}
}

__attribute__((noinline, section(".ramfunc"))) void delay_cycles(uint32_t cycles) {
  cycles /= 4;

  asm volatile(
    "1: sub %[cycles], %[cycles], #1 \n"
    "   nop \n"
    "   bne 1b \n"
    : [cycles] "+l"(cycles));
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
  uint32_t currentTicks = 0;
  boardInit();
  currentDisplay.init();
  dsPuts(&displayStream, "Hello World!");
  while (1) {
    delay_cycles(10);
    __NOP();
    if (currTicks != systicks) {
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
      sioGpioOutXor(SIO, LED_MASK);
      currTicks = systicks;
    }
  }
}
