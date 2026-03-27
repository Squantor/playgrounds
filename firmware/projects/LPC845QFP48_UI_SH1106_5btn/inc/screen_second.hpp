/**
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2026 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 *
 * @file screen_second.hpp
 * @brief Secondary screen definition
 *
 */
#ifndef SCREEN_SECOND_HPP
#define SCREEN_SECOND_HPP

#include "event_handler.hpp"
#include "user_interface.hpp"
#include "mid/gfx_display_wrap.hpp"
#include "application_font.hpp"

template <auto &display>
class Second_screen : public User_interface_screen<Button>, public Event_handler {
 public:
  Second_screen() : entry_count(0), event_count(0), enter_count(0), user_interface(nullptr) {}
  void setup(User_interface<Button> *current_user_interface) override {
    user_interface = current_user_interface;
  }
  void handle_button(Button button) override {
    switch (button) {
      case Button::Button1Down:
        enter_count++;
        break;

      case Button::Button0Down:
        user_interface->previous_screen();
        break;

      case Button::Button2Down:
        user_interface->next_screen();
        break;

      default:
        command_console.print("Main screen: Unhandled button\n");
        return;
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
      libmcumid::Dec dec_enter_count{static_cast<std::int32_t>(enter_count)};
      display.clear();
      display.print("Second screen.\nIn tha house!\n", application_font);
      display.print("Enter count: ", application_font);
      display.print(dec_enter_count, application_font);
      display.print("\n", application_font);
      display.flip();
    }
  }
  std::size_t entry_count;
  std::size_t event_count;
  std::size_t enter_count;
  User_interface<Button> *user_interface;
  bool is_active;
};

#endif