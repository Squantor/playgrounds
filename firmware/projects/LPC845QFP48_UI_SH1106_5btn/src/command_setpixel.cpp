/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2026 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 * @file command_setpixel.cpp
 * @brief Command for setting a pixel
 */
#include <commands.hpp>
#include <application.hpp>
#include <libmcu/bitmap/bitmap_view.hpp>

squLib::results setpixel(std::span<const char>) {
  if (command_values.size() < 3) {
    command_console.print("3 arguments needed: x, y, pixel value\n");
    return squLib::results::error;
  }
  std::int32_t x, y, pixel;
  command_values.pop(pixel);
  command_values.pop(y);
  command_values.pop(x);
  ui_display.set_pixel(x, y, pixel);
  ui_display.flip();
  return squLib::results::ok;
}

squLib::commandHandler command_handler_setpixel{"setpixel", "Sets a pixel on position x,y to pixel value\n", setpixel};
