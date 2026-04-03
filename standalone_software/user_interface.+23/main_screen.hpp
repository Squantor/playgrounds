/**
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2026 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 *
 * @file main_screen.hpp
 * @brief Main screen definition
 */
#ifndef MAIN_SCREEN_HPP
#define MAIN_SCREEN_HPP

#include "events.hpp"
#include "user_interface.hpp"

class Main_screen : public User_interface_screen<Button>, public Event_handler {
 public:
  Main_screen(Display &application_display)
    : display(application_display), entry_count(0), event_count(0), user_interface(nullptr) {}
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
        printf("Main screen: Unhandled button\n");
        break;
    }
    render(display);
  }
  void activate() override {
    is_active = true;
    entry_count++;
    render(display);
  }
  void deactivate() override {
    is_active = false;
  }
  void handle_event(EventData event) {
    switch (event.event) {
      case Events::Special:
        event_count++;
        break;
      default:
        break;
    }
    render(display);
  }

 private:
  void render(Display &display) {
    if (is_active) {
      char stringbuf[64];
      display.print("Main screen\n");
      snprintf(stringbuf, sizeof(stringbuf), "%zu entry counts\n%zu event counts\n", entry_count, event_count);
      display.print(stringbuf);
      display.flip();
    }
  }
  Display &display;
  std::size_t entry_count;
  std::size_t event_count = 0;
  User_interface<Button> *user_interface;
  bool is_active;
};

#endif