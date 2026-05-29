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
#include <screen_second.hpp>
#include <screen_menu.hpp>
#include <menu_item.hpp>
#include <menu_item_value_dummy.hpp>
#include <menu_item_exit.hpp>
#include <menu_item_contrast.hpp>
#include <user_interface_events.hpp>

squLib::console<usart_peripheral> command_console;
squLib::commandValueStack<8, command_console> command_values;
squLib::commandInterpreter<commandHandlers, command_values, command_console> command_interpreter;
squLib::commandlineSimple<40, command_console, command_interpreter> command_line;

Buttons buttons{0xFF, event_dispatcher};

Menu_item_contrast contrast_menu_item;
Menu_item_value_dummy first_menu_item(Menu_item_type::value, "First", 1);
Menu_item_value_dummy second_menu_item(Menu_item_type::value, "Second", 2);
Menu_item_value_dummy third_menu_item(Menu_item_type::value, "Third", 3);
Menu_item_exit exit_menu;

std::array<Menu_item* const, 5> menu_items = {&contrast_menu_item, &first_menu_item, &second_menu_item, &third_menu_item,
                                              &exit_menu};

Main_screen<application_display> main_screen;
Second_screen<application_display> second_screen;
Menu_screen<application_display> menu_screen(menu_items);

std::array<User_interface_screen<User_interface_events>*, 3> screens = {&main_screen, &second_screen, &menu_screen};
User_interface<Button, User_interface_events> user_interface{screens};

ButtonHandler button_handler;
std::array<const EventHandlerPair, 3> event_handlers = {
  EventHandlerPair{&button_handler, Events::Button},
  EventHandlerPair{&user_interface, Events::Button},
  EventHandlerPair{&main_screen, Events::Seconds},
};
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
  // second event generator
  static std::uint32_t currentTicks = ticks;
  if (currentTicks + ticks_per_second < ticks) {
    event_dispatcher.PostEvent(Event_data{.event = Events::Seconds, .seconds = ticks / ticks_per_second});
    currentTicks = ticks;
  }

  // command line
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
