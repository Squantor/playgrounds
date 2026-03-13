/**
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2026 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 *
 * @file screen_main.hpp
 * @brief Main screen definition
 *
 */
#ifndef SCREEN_MAIN_HPP
#define SCREEN_MAIN_HPP

#include "event_handler.hpp"
#include "user_interface.hpp"
#include "mid/gfx_display_wrap.hpp"
#include "application_font.hpp"

template <auto &display>
class Main_screen : public User_interface_screen<Button>, public Event_handler {
 public:
  Main_screen() : entry_count(0), event_count(0), user_interface(nullptr) {}
  void setup(User_interface<Button> *current_user_interface) override {
    user_interface = current_user_interface;
  }
  void handle_button(Button button) override {
    switch (button) {
      case Button::Button1Down:
        break;

      case Button::Button0Down:
        user_interface->previous_screen();
        break;

      case Button::Button2Down:
        user_interface->next_screen();
        break;

      default:
        command_console.print("Main screen: Unhandled button\n");
        break;
    }
    render();
  }
  void activate() override {
    is_active = true;
    entry_count++;
    render();
  }
  void deactivate() override {
    is_active = false;
  }
  void handle_event(Event_data event) {
    (void)event;
    render();
  }

 private:
  void render() {
    if (is_active) {
      display.clear();
      // char stringbuf[64];
      display.print("Main screen\nturn on \n", application_font);
      // snprintf(stringbuf, sizeof(stringbuf), "%zu entry counts\n%zu event counts\n", entry_count, event_count);
      // display.print(stringbuf);
      display.flip();
    }
  }
  std::size_t entry_count;
  std::size_t event_count = 0;
  User_interface<Button> *user_interface;
  bool is_active;
};

#endif