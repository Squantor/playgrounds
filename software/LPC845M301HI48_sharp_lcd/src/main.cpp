/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2021 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/*
 * This is simple example file which does do any I/O and thus
 * can be compiled and run on any Cortex-M MCU. However, to see
 * its effect, you'll need to use debugger.
 */
#include <nuclone_LPC845M301BD48_sharp_lcd.hpp>
#include <sharp_memlcd.hpp>
#include <font.hpp>

volatile unsigned int systicks = 0;
volatile bool pinmode;

extern "C" {
void SysTick_Handler(void) {
  gpioPortToggle(GPIO, PORT_LED, 1 << PIN_LED);
  systicks = systicks + 1;
}
}

void waitSpiTxComplete(void) {
  while (!(spiSetGetStatus(SPI0, 0x0) & SPI_STAT_TXRDY))
    ;
}

void lcdTransfer(uint16_t *begin, uint16_t *end) {
  // transfer of 1
  if (begin + 1 == end) {
    waitSpiTxComplete();
    spiSetTxCtrlData(SPI0, SPI_TXDATCTL_TXDAT(*begin) | SPI_TXDATCTL_TXSSEL0 |
                               SPI_TXDATCTL_EOF | SPI_TXDATCTL_EOT |
                               SPI_TXDATCTL_RXIGNORE | SPI_TXDATCTL_LEN(16));
    return;
  }
  // transfer of N
  else {
    uint16_t *p = begin;
    while (p < end) {
      waitSpiTxComplete();
      spiSetTxCtrlData(SPI0, SPI_TXDATCTL_TXDAT(*p) | SPI_TXDATCTL_TXSSEL0 |
                                 SPI_TXDATCTL_EOF | SPI_TXDATCTL_RXIGNORE |
                                 SPI_TXDATCTL_LEN(16));
      p++;
    }
    // line or multiline transfers need to be terminated
    waitSpiTxComplete();
    spiSetTxCtrlData(SPI0, SPI_TXDATCTL_TXDAT(0x0000) | SPI_TXDATCTL_TXSSEL0 |
                               SPI_TXDATCTL_EOF | SPI_TXDATCTL_EOT |
                               SPI_TXDATCTL_RXIGNORE | SPI_TXDATCTL_LEN(16));
  }
}

util::sharpMemLcd<util::LS027B7DH01> boardLcd;

int main() {
  pinmode = false;
  unsigned int currticks = systicks;
  boardInit();
  boardLcd.init();
  boardLcd.setBuffer(0xFFFF);
  while (1) {
    if (currticks < systicks) {
      currticks = systicks;
      /*
      for(unsigned int i = 0 ; i < boardLcd.maxY; i++)
      {
          for(unsigned int j = 0; j < boardLcd.maxX; j++)
          {
              boardLcd.putPixel(j, i, ((j ^ i) + (currticks/2)) & 0x40);
              //boardLcd.putPixel(i, j, ((i*i + j*j) + currticks) & 0x20);
              //if(i == j) boardLcd.putPixel(i, j, 1);
          }
      }*/
      boardLcd.bitBlockTransfer(0, 0, font8x8 + ascii2font8x8['H'], 8, 8, true);
      boardLcd.bitBlockTransfer(8, 8, font8x8 + ascii2font8x8['e'], 8, 8, true);
      boardLcd.bitBlockTransfer(16, 16, font8x8 + ascii2font8x8['l'], 8, 8,
                                true);
      boardLcd.bitBlockTransfer(24, 24, font8x8 + ascii2font8x8['l'], 8, 8,
                                true);
      boardLcd.bitBlockTransfer(32, 32, font8x8 + ascii2font8x8['o'], 8, 8,
                                true);
      boardLcd.bitBlockTransfer(40, 40, font8x8 + ascii2font8x8[' '], 8, 8,
                                true);
      boardLcd.bitBlockTransfer(48, 48, font8x8 + ascii2font8x8['w'], 8, 8,
                                true);
      boardLcd.bitBlockTransfer(56, 56, font8x8 + ascii2font8x8['o'], 8, 8,
                                true);
      boardLcd.bitBlockTransfer(64, 64, font8x8 + ascii2font8x8['r'], 8, 8,
                                true);
      boardLcd.bitBlockTransfer(72, 72, font8x8 + ascii2font8x8['l'], 8, 8,
                                true);
      boardLcd.bitBlockTransfer(80, 80, font8x8 + ascii2font8x8['d'], 8, 8,
                                true);
      boardLcd.bitBlockTransfer(88, 88, font8x8 + ascii2font8x8['!'], 8, 8,
                                true);
      boardLcd.flipVcom(lcdTransfer);
      boardLcd.lcdUpdate(lcdTransfer);
    }
    __NOP();
  }
}
