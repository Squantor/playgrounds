/**
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2026 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 *
 * @file second_screen.hpp
 * @brief Second screen definition
 */
#ifndef SECOND_SCREEN_HPP
#define SECOND_SCREEN_HPP

#include "events.hpp"
#include "user_interface.hpp"

class Second_screen : public User_interface_screen<Button> {
 public:
  Second_screen(Display &application_display)
    : display(application_display), entry_count(0), user_interface(nullptr), is_active(false) {}
  void setup(User_interface<Button> *current_user_interface) override {
    user_interface = current_user_interface;
  }
  void handle_button(Button button) override {
    switch (button) {
      case Button::MenuEnterPress:
        break;

      case Button::MenuLeftPress:
        user_interface->previous_screen();
        break;

      case Button::MenuRightPress:
        user_interface->next_screen();
        break;

      default:
        printf("Second screen: Unhandled button\n");
        break;
    }
    render(display);
  }
  void activate() override {
    entry_count++;
    is_active = true;
    render(display);
  }
  void deactivate() override {
    is_active = false;
  }

 private:
  void render(Display &display) {
    if (is_active) {
      char stringbuf[32];
      display.print("Second screen\n");
      snprintf(stringbuf, sizeof(stringbuf), "%zu entry counts\n", entry_count);
      display.print(stringbuf);
      display.flip();
    }
  }
  Display &display;
  std::size_t entry_count;
  User_interface<Button> *user_interface;
  bool is_active;
};

#endif