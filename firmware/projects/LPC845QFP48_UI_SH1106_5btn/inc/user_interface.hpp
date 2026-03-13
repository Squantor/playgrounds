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
  /**
   * @brief Sets up the screen with the user interface
   */
  virtual void setup(User_interface<Button_enum> *) = 0;
  /**
   * @brief Handles button events, only called when screen is active
   */
  virtual void handle_button(Button_enum) = 0;
  /**
   * @brief Activates the screen
   */
  virtual void activate() = 0;
  /**
   * @brief Deactivates the screen
   */
  virtual void deactivate() = 0;
};

template <typename Button_enum>
struct User_interface : public Event_handler {
  User_interface(std::span<User_interface_screen<Button_enum> *> application_screens)
    : current_screen_index(0), screens(application_screens) {}

  void init() {
    for (auto &screen : screens) {
      screen->setup(this);
    }
    screens[current_screen_index]->activate();
  }

  void handle_event(Event_data event) override {
    if (event.event != Events::Button) {
      return;
    }
    screens[current_screen_index]->handle_button(event.button);
  }

  void next_screen() {
    if ((current_screen_index + 1) < screens.size()) {
      screens[current_screen_index]->deactivate();
      current_screen_index++;
      screens[current_screen_index]->activate();
    }
  }

  void previous_screen() {
    if (current_screen_index > 0) {
      screens[current_screen_index]->deactivate();
      current_screen_index--;
      screens[current_screen_index]->activate();
    }
  }

 private:
  std::size_t current_screen_index;
  std::span<User_interface_screen<Button_enum> *> screens;
};

#endif