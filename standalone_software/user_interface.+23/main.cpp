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

User_interface user_interface;
std::array<EventHandlerPair, 1> handlers = {{&user_interface, Events::Button}};
EventDispatcher dispatcher(handlers);

/**
 * @brief main entrypoint
 * @return error code to operating system
 */
int main(int argc, char *argv[]) {
  (void)argc;
  (void)argv;
  printf("Press q to quit, a for left, d for enter, f for right\n");
  int key = getchar();
  while (key != 'q') {
    if (key == 'a') {
      dispatcher.PostEvent({Events::Button, Button::MenuLeftPress});
    } else if (key == 'd') {
      dispatcher.PostEvent({Events::Button, Button::MenuEnterPress});
    } else if (key == 'f') {
      dispatcher.PostEvent({Events::Button, Button::MenuRightPress});
    }
    dispatcher.Process();
    key = getchar();
  }
  return 0;
}
