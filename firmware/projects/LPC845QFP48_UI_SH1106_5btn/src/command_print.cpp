/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2025 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 * @file command_print.cpp
 * @brief prints a character on the SH1106 OLED display
 */
#include <commands.hpp>
#include <application.hpp>
#include <algorithm>
#include <fonts/font_8x8_rowflip.hpp>

sqEmbedded::fonts::mono8x8RowFlip font;

std::array<std::uint8_t, 8> character_buffer;

squLib::results print(std::span<const char>) {
  if (command_values.size() < 4) {
    command_console.print("Needs 4 elements from top to bottom: character, count, column, row\n");
    return squLib::results::error;
  }
  std::int32_t col, row, length, character;
  command_values.pop(character);
  command_values.pop(length);
  command_values.pop(col);
  command_values.pop(row);
  ui_display.SetAddress(static_cast<uint32_t>(col), static_cast<uint32_t>(row));
  std::array<std::uint8_t, 8> buffer = font.ascii2Bitmap(static_cast<uint8_t>(character));
  std::copy_n(buffer.begin(), buffer.size(), character_buffer.begin());
  for (int i = 0; i < length; i++) {
    ui_display.SendData(character_buffer);
  }
  return squLib::results::ok;
}

squLib::commandHandler print_handler{
  "print", "prints a character on col,row of the OLED display\n stack format col, row, character\n", print};
