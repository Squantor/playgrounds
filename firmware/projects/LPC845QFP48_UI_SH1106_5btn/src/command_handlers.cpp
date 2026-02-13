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
#include <command_handlers.hpp>
#include <application.hpp>
#include <commands.hpp>

squLib::results helpFunction(std::span<const char> commandLine);

squLib::commandHandler helpHandler{"help", "Prints out all help commands\n", helpFunction};
squLib::commandHandler numberHandler{"0??", "Any integer will get pushed on the stack\n", nullptr};
squLib::commandHandler hexNumHandler{"0x0?", "Any hex unsigned integer will get pushed on the stack\n", nullptr};

squLib::results helpFunction(std::span<const char> commandLine) {
  (void)commandLine;
  command_interpreter.printHelp();
  return squLib::results::ok;
}

std::array<squLib::commandHandler, 16> commandHandlerTable{helpHandler,          numberHandler,
                                                           hexNumHandler,        stk_handler,
                                                           empty_handler,        drop_handler,
                                                           dup_handler,          stat_handler,
                                                           contrast_handler,     block_handler,
                                                           print_handler,        command_handler_button,
                                                           command_handler_blit, command_handler_setpixel,
                                                           command_handler_cat,  command_handler_glyph};
std::span<const squLib::commandHandler> commandHandlers{commandHandlerTable};
