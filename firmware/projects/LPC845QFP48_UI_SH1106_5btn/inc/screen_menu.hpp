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
#include "menu_item.hpp"

/**
 * @brief Menu screen
 * @tparam &display
 */
template <auto &display>
class Menu_screen : public User_interface_screen<Button>, public Event_handler {
 public:
  Menu_screen(std::span<Menu_item *const> menu_items) : is_active(false), user_interface(nullptr), items(menu_items) {}
  void setup(User_interface<Button> *current_user_interface) override {
    user_interface = current_user_interface;
  }
  void handle_button(Button button) override {
    switch (button) {
      case Button::Button1Down:
        is_menu_active = !is_menu_active;
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
    is_menu_active = false;
    menu_index = 0;
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
      if (is_menu_active) {
        display.print("Menu screen active\n", application_font);
      } else {
        display.print("Menu screen inactive\n", application_font);
      }
      display.flip();
    }
  }
  bool is_active;
  bool is_menu_active;
  std::size_t menu_index;
  User_interface<Button> *user_interface;
  std::span<Menu_item *const> items;
};

#endif