/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2024 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 * @file gathering place for all command handlers
 * @brief definitions for all command handlers
 */
#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <command_handler.hpp>

extern squLib::commandHandler stk_handler;
extern squLib::commandHandler empty_handler;
extern squLib::commandHandler dup_handler;
extern squLib::commandHandler drop_handler;
extern squLib::commandHandler stat_handler;
extern squLib::commandHandler contrast_handler;
extern squLib::commandHandler block_handler;
extern squLib::commandHandler print_handler;
extern squLib::commandHandler command_handler_button;
extern squLib::commandHandler command_handler_blit;
extern squLib::commandHandler command_handler_setpixel;
extern squLib::commandHandler command_handler_cat;

#endif