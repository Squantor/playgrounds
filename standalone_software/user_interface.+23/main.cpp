/*
SPDX-License-Identifier: MIT

Copyright (c) 2026 Bart Bilos
For conditions of distribution and use, see LICENSE file
*/
/**
 * \file main.cpp
 * Main entrypoint for executing template application
 */
#include <cstdio>
#include <array>
#include "event_dispatch.hpp"
#include "user_interface.hpp"
#include "display.hpp"

using Application_screen = User_interface_screen<Button>;
using Application_user_interface = User_interface<Button>;

template <std::uint16_t x_size, std::uint16_t y_size>
class Test_display : public Display {
 public:
  void print(const char *message) override {
    printf("Display print: %s", message);
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

class Main_screen : public Application_screen {
 public:
  Main_screen() : entry_count(0) {}
  void handle_button(Application_user_interface *user_interface, Button button) override {
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
  }
  void enter_screen() override {
    entry_count++;
  }
  void exit_screen() override {}
  void render(Display &display) override {
    char stringbuf[32];
    display.print("Main screen\n");
    snprintf(stringbuf, sizeof(stringbuf), "%zu entry counts\n", entry_count);
    display.print(stringbuf);
    display.flip();
  }

 private:
  std::size_t entry_count;
};

class Second_screen : public Application_screen {
 public:
  Second_screen() : entry_count(0) {}
  void handle_button(Application_user_interface *user_interface, Button button) override {
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
  }
  void enter_screen() override {
    entry_count++;
  }
  void exit_screen() override {}
  void render(Display &display) override {
    char stringbuf[32];
    display.print("Second screen\n");
    snprintf(stringbuf, sizeof(stringbuf), "%zu entry counts\n", entry_count);
    display.print(stringbuf);
    display.flip();
  }

 private:
  std::size_t entry_count;
};

class Menu_screen : public Application_screen {
 public:
  Menu_screen() : entry_count(0) {}
  void handle_button(Application_user_interface *user_interface, Button button) override {
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
  }
  void enter_screen() override {
    entry_count++;
  }
  void exit_screen() override {}
  void render(Display &display) override {
    char stringbuf[32];
    display.print("Menu screen\n");
    snprintf(stringbuf, sizeof(stringbuf), "%zu entry counts\n", entry_count);
    display.print(stringbuf);
    display.flip();
  }

 private:
  std::size_t entry_count;
};

Test_display<320, 240> display;

Main_screen main_screen;
Second_screen second_screen;
Menu_screen menu_screen;

std::array<Application_screen *, 3> screens = {{&main_screen, &second_screen, &menu_screen}};
User_interface<Button> user_interface(display, screens);

std::array<EventHandlerPair, 1> handlers = {{&user_interface, Events::Button}};
EventDispatcher dispatcher(handlers);

/**
 * @brief main entrypoint
 * @return error code to operating system
 */
int main(int, char *[]) {
  printf("Press q to quit, a for left, s for enter, d for right\n");
  int key = 0;
  user_interface.init();
  while (key != 'q') {
    if (key == 'a') {
      dispatcher.PostEvent({Events::Button, Button::MenuLeftPress});
    } else if (key == 's') {
      dispatcher.PostEvent({Events::Button, Button::MenuEnterPress});
    } else if (key == 'd') {
      dispatcher.PostEvent({Events::Button, Button::MenuRightPress});
    }
    dispatcher.Process();
    key = getchar();
  }
  return 0;
}
