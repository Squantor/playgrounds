/**
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2026 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 *
 * @file user_interface.cpp
 * @brief Embedded user interface library implementation
 *
 */
#include "user_interface.hpp"
#include <cstdio>

void User_interface::HandleEvent(EventData event) {
  switch (event.event) {
    case Events::Button:
      printf("Button event\n");
      break;
    default:
      printf("Unhandled event\n");
      return;
  }
  switch (event.button) {
    case Button::MenuEnterPress:
      printf("Menu enter button\n");
      break;

    case Button::MenuLeftPress:
      printf("Menu left button\n");
      break;

    case Button::MenuRightPress:
      printf("Menu right button\n");
      break;

    default:
      printf("Unhandled button\n");
      break;
  }
}