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
#include <libmcu/bitmap/blit.hpp>

std::array<std::uint32_t, 8> glyph_buffer;
libmcu::bitmap::Bitmap bitmap_glyph(glyph_buffer.data(), 8, 8, 1);

squLib::results glyph(std::span<const char>) {
  if (command_values.size() < 3) {
    command_console.print("3 arguments needed: x, y, glyph index\n");
    return squLib::results::error;
  }
  std::int32_t x, y, index;
  command_values.pop(index);
  command_values.pop(y);
  command_values.pop(x);
  application_font.get_glyph(static_cast<char>(index), bitmap_glyph);
  ui_display.blit(x, y, bitmap_glyph);
  ui_display.flip();
  return squLib::results::ok;
}

squLib::commandHandler command_handler_glyph{"glyph", "Blits a glyph to the screen on x,y\n", glyph};
