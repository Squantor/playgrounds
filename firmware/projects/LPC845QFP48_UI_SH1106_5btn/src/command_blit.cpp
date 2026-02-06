/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2024 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 * @file command_empty.cpp
 * @brief Empty command template file
 */
#include <commands.hpp>
#include <application.hpp>
#include <libmcu/bitmap/bitmap_view.hpp>

std::array<std::uint32_t, 32> bitmap_buffer;

squLib::results blit(std::span<const char>) {
  if (command_values.size() < 5) {
    command_console.print("5 arguments needed: x, y, width, height, pattern\n");
    return squLib::results::error;
  }
  std::int32_t x, y, width, height, pattern;
  command_values.pop(pattern);
  command_values.pop(height);
  command_values.pop(width);
  command_values.pop(y);
  command_values.pop(x);
  bitmap_buffer.fill(static_cast<std::uint32_t>(pattern));
  libmcu::bitmap::Bitmap(bitmap_buffer.data(), width, height, 1);
  //  blit bitmap
  //  ui_display.SetAddress(static_cast<uint32_t>(col), static_cast<uint32_t>(row));
  //  ui_display.SendData(std::span<uint8_t>(pattern_buffer).subspan(0, length));
  return squLib::results::ok;
}

squLib::commandHandler command_handler_blit{"blit", "Blits a pattern to the screen on x,y, width, height, pattern\n", blit};
