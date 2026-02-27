/**
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2026 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 *
 * @file user_interface.hpp
 * @brief Embedded user interface library interface
 *
 */
#ifndef USER_INTERFACE_HPP
#define USER_INTERFACE_HPP

#include <span>
#include <cstdio>
#include <cstdint>
#include "display.hpp"
#include "event_dispatch.hpp"

/**
 * @brief User interface forward declaration
 * @tparam Button_enum Enumeration used for button events
 */
template <typename Button_enum>
struct User_interface;

template <typename Button_enum>
struct User_interface_screen {
  virtual void handle_button(User_interface<Button_enum> *, Button_enum) = 0;
  virtual void enter_screen() = 0;
  virtual void exit_screen() = 0;
  virtual void render(Display &display) = 0;
};

template <typename Button_enum>
struct User_interface : public EventHandler {
  User_interface(Display &application_display, std::span<User_interface_screen<Button_enum> *> application_screens)
    : current_screen_index(0), display(application_display), screens(application_screens) {}

  void init() {
    screens[current_screen_index]->render(display);
  }

  void HandleEvent(EventData event) override {
    switch (event.event) {
      case Events::Button:
        break;
      default:
        printf("Unhandled event\n");
        return;
    }
    screens[current_screen_index]->handle_button(this, event.button);
    screens[current_screen_index]->render(display);
  }

  void next_screen() {
    if ((current_screen_index + 1) < screens.size()) {
      screens[current_screen_index]->exit_screen();
      current_screen_index++;
      screens[current_screen_index]->enter_screen();
    }
  }

  void previous_screen() {
    if (current_screen_index > 0) {
      screens[current_screen_index]->exit_screen();
      current_screen_index--;
      screens[current_screen_index]->enter_screen();
    }
  }

 private:
  std::size_t current_screen_index;
  Display &display;
  std::span<User_interface_screen<Button_enum> *> screens;
};

#endif