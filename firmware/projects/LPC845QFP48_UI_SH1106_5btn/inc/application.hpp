/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2024 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 * @brief main application class
 */
#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <LPC845QFP48_UI_SH1106_5btn.hpp>
#include <command_interpreter_number.hpp>
#include <command_value_stack.hpp>
#include <command_handlers.hpp>
#include <console.hpp>
#include <event_dispatch.hpp>

enum class ApplicationState : std::uint8_t {
  idle, /*!< idle state */
};

class Application {
 public:
  Application() : state{ApplicationState::idle} {}
  void Init();
  void Progress();
  ApplicationState GetState() {
    return state;
  }

 private:
  ApplicationState state;
};

extern squLib::console<usart_peripheral> command_console;
extern squLib::commandValueStack<8, command_console> command_values;
extern squLib::commandInterpreter<commandHandlers, command_values, command_console> command_interpreter;
extern Application controller;
extern EventDispatcher event_dispatcher;

#endif