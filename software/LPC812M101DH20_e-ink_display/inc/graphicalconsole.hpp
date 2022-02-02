/*
SPDX-License-Identifier: MIT

Copyright (c) 2022 Bart Bilos
For conditions of distribution and use, see LICENSE file
*/
#ifndef GRAPHICAL_CONSOLE_HPP
#define GRAPHICAL_CONSOLE_HPP

#include <cinttypes>
#include <font_8x8.h>
#include <bit.h>

template <uint8_t maxX, uint8_t maxY>
struct graphicalConsole {
  graphicalConsole(const uint8_t *font) : xpos{0}, ypos{0}, font{font} {}
  void writeChar(auto writeWindow, char c) {
    writeWindow(xpos, xpos + 7, ypos, ypos, ascii2Font8x8(font, c), 8);
    xpos += 8;
    if (xpos >= maxX) {
      xpos = 0;
      ypos += 8;
    }
    if (ypos >= maxY) {
      ypos = 0;
    }
  }
  void writeBigChar(auto writeWindow, char c) {
    const uint8_t *bitmap = ascii2Font8x8(font, c);
    uint8_t bigBitmap[32];
    for (size_t i = 0; i < 16; i++) {
      uint16_t zoomedData = bitZoom(*bitmap);
      bigBitmap[i] = zoomedData;
      bigBitmap[i + 16] = zoomedData >> 8;
      i++;
      bigBitmap[i] = zoomedData;
      bigBitmap[i + 16] = zoomedData >> 8;
      bitmap++;
    }
    writeWindow(xpos, xpos + 15, ypos, ypos + 8, bigBitmap, 32);
    xpos += 16;
    if (xpos >= maxX) {
      xpos = 0;
      ypos += 16;
    }
    if (ypos >= maxY) {
      ypos = 0;
    }
  }
  uint8_t xpos;
  uint8_t ypos;
  const uint8_t *const font;
};

#endif