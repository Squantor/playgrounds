/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2024 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 * @file command handlers definitions
 * @brief central gathering spot for all command handlers
 */
#include <commands.hpp>
#include <application.hpp>

squLib::results stat(std::span<const char> commandLine) {
  (void)commandLine;
  switch (controller.GetState()) {
    case ApplicationState::idle:
      command_console.print("Application is idle\n");
      break;

    default:
      command_console.print("Unknown state!\n");
      break;
  }
  return squLib::results::ok;
}

squLib::commandHandler stat_handler{"stat", "prints the current application state\n", stat};
