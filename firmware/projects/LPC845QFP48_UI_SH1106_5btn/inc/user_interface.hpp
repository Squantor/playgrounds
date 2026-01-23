/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2026 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 * @file user_interface.hpp
 * @brief user interface class definitions
 */
#ifndef USER_INTERFACE_HPP
#define USER_INTERFACE_HPP

#include <span>
#include <event_handler.hpp>
#include <ui_screen.hpp>

class UserInterface : public EventHandler {
 public:
  UserInterface(std::span<UserInterfaceScreen> screens) : top_screens(screens) {}
  void Init() {}
  void Progress() {}
  void HandleEvent(EventData event);

 private:
  std::span<UserInterfaceScreen> top_screens;
};

#endif