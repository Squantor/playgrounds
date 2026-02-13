/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2026 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 * @file command_glyph.cpp
 * @brief Blits a glyph to the display
 */
#include <commands.hpp>
#include <application.hpp>
#include <application_font.hpp>

squLib::results glyph(std::span<const char>) {
  if (command_values.size() < 3) {
    command_console.print("3 arguments needed: x, y, glyph index\n");
    return squLib::results::error;
  }
  std::int32_t x, y;
  command_values.pop(y);
  command_values.pop(x);
  // index glyph and get bitmap
  // ui_display.blit(x, y, bitmap);
  ui_display.flip();
  return squLib::results::ok;
}

squLib::commandHandler command_handler_glyph{"glyph", "Blits a glyph to the screen on x,y\n", glyph};
