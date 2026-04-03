/**
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2026 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 *
 * @file main.cpp
 * @brief Embedded user interface library implementation
 */
#include <cstdio>
#include <array>
#include "event_dispatch.hpp"
#include "user_interface.hpp"
#include "display.hpp"
#include "main_screen.hpp"
#include "second_screen.hpp"
#include "menu_screen.hpp"

enum class Screens_names : std::uint8_t {
  Main,
  Second,
  Menu,
  End
};

// using Application_screen = User_interface_screen<Button>;
// using Application_user_interface = User_interface<Button>;

template <std::uint16_t x_size, std::uint16_t y_size>
class Test_display : public Display {
 public:
  void print(const char *message) override {
    puts(message);
  }
  void flip() override {
    printf("Display flip\n");
  }
  std::uint16_t get_x_size() override {
    return x_size;
  }
  std::uint16_t get_y_size() override {
    return y_size;
  }
};

class Menu_screen : public User_interface_screen<Button> {
 public:
  Menu_screen(Display &application_display)
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
        printf("Menu screen: Unhandled button\n");
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
      display.print("Menu screen\n");
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

Test_display<320, 240> display;

Main_screen main_screen(display);
Second_screen second_screen(display);
Menu_screen menu_screen(display);

std::array<User_interface_screen<Button> *, 3> screens = {{&main_screen, &second_screen, &menu_screen}};
User_interface<Button> user_interface(screens);

std::array<Event_handler_pair, 2> handlers = {{{&user_interface, Events::Button}, {&main_screen, Events::Special}}};
Event_dispatcher dispatcher(handlers);

/**
 * @brief main entrypoint
 * @return error code to operating system
 */
int main(int, char *[]) {
  printf("Press q to quit, a for left, s for enter, d for right, e for event\n");
  int key = 0;
  user_interface.init();
  while (key != 'q') {
    if (key == 'a') {
      dispatcher.post_event({.event = Events::Button, .button = Button::MenuLeftPress});
    } else if (key == 's') {
      dispatcher.post_event({.event = Events::Button, .button = Button::MenuEnterPress});
    } else if (key == 'd') {
      dispatcher.post_event({.event = Events::Button, .button = Button::MenuRightPress});
    } else if (key == 'e') {
      dispatcher.post_event({.event = Events::Special, .special = Various::None});
    }
    dispatcher.process();
    key = getchar();
  }
  return 0;
}
