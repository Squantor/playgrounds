/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2025 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 * @file command_contr.cpp
 * @brief Command for setting Oled display contrast
 */
#include <commands.hpp>
#include <application.hpp>

squLib::results Contrast(std::span<const char> commandLine) {
  (void)commandLine;
  if (command_values.size() == 0) {
    command_console.print("Stack is empty\n");
    return squLib::results::error;
  }
  std::int32_t contrast = 10;
  command_values.pop(contrast);
  ui_display.Contrast(static_cast<std::uint8_t>(contrast));
  return squLib::results::ok;
}

squLib::commandHandler contrast_handler{"contr", "Sets the OLED display contrast\n", Contrast};
