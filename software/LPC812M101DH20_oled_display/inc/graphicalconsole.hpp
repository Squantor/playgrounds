/*
SPDX-License-Identifier: MIT

Copyright (c) 2022 Bart Bilos
For conditions of distribution and use, see LICENSE file
*/
#ifndef GRAPHICAL_CONSOLE_HPP
#define GRAPHICAL_CONSOLE_HPP

#include <cinttypes>
#include <font_8x8.h>

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
  uint8_t xpos;
  uint8_t ypos;
  const uint8_t *const font;
};

#endif