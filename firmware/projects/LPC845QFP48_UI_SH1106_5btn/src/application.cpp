/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2024 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 * @brief main application entry point
 */

#include <application.hpp>
#include <cmdline_simple.hpp>
#include <console.hpp>
#include <event_dispatch.hpp>
#include <button_handler.hpp>
#include <buttons.hpp>
#include <user_interface.hpp>
#include <screen_main.hpp>

squLib::console<usart_peripheral> command_console;
squLib::commandValueStack<8, command_console> command_values;
squLib::commandInterpreter<commandHandlers, command_values, command_console> command_interpreter;
squLib::commandlineSimple<80, command_console, command_interpreter> command_line;

Buttons buttons{0xFF, event_dispatcher};

Main_screen<application_display> main_screen;

std::array<User_interface_screen<Button>*, 1> screens = {&main_screen};
User_interface<Button> user_interface{screens};

ButtonHandler button_handler;
std::array<const EventHandlerPair, 2> event_handlers = {EventHandlerPair{&button_handler, Events::Button},
                                                        EventHandlerPair{&user_interface, Events::Button}};
EventDispatcher event_dispatcher{event_handlers};

auto button_call_lambda = [](std::uint8_t port_data) {
  buttons.SetPortData(port_data);
};

void Application::Init() {
  command_console.print("LPC845 small nuclone SH1106 test program\n");
  ui_port_expander.RegisterCallback(button_call_lambda);
  while (ui_display.state != libmcu::States::Idle) {
    BoardProgress();
  }
  user_interface.init();
}

void Application::Progress() {
  static std::uint32_t currentTicks = ticks;
  if (currentTicks + 100 < ticks) {
    // Print("test:\t", currentTicks, "\t", print::Hex{currentTicks}, "\n");
    currentTicks = ticks;
  }
  // echo characters
  if (usart_peripheral.GetReceiveLevel() > 0) {
    static std::array<char, 1> data;
    usart_peripheral.Receive(data);
    command_line.input(data);
  }
  // state handling
  switch (state) {
    case ApplicationState::idle:
      break;

    default:
      command_console.print("Unknown state!!!");
      break;
  }
}
