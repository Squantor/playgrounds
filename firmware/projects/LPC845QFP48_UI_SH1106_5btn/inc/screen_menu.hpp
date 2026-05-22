/**
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2026 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 *
 * @file screen_menu.hpp
 * @brief Menu screen definition
 *
 */
#ifndef SCREEN_MENU_HPP
#define SCREEN_MENU_HPP

#include "event_handler.hpp"
#include "user_interface.hpp"
#include "mid/gfx_display.hpp"
#include "application_font.hpp"
#include "LPC845QFP48_UI_SH1106_5btn.hpp"

/**
 * @brief Menu screen
 * @tparam &display
 */
template <auto &display>
class Menu_screen : public User_interface_screen<Button>, public Event_handler {
 public:
  Menu_screen() : user_interface(nullptr) {}
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
        command_console.print("Main screen: Unhandled button event\n");
        return;
        break;
    }
    render();
  }
  void activate() override {
    is_active = true;
    render();
  }
  void deactivate() override {
    is_active = false;
  }
  void handle_event(Event_data event) {
    switch (event.event) {
      case Events::Seconds:

        break;

      default:
        break;
    }
    render();
  }

 private:
  void render() {
    if (is_active) {
      display.clear();
      display.print("Menu screen\n", application_font);
      display.flip();
    }
  }
  User_interface<Button> *user_interface;
  bool is_active;
};

#endif