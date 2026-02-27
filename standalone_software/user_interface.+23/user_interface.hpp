/**
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2026 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 *
 * @file user_interface.hpp
 * @brief Embedded user interface library interface
 *
 */
#ifndef USER_INTERFACE_HPP
#define USER_INTERFACE_HPP
#include "event_dispatch.hpp"

struct User_interface : public EventHandler {
  User_interface() {}
  void HandleEvent(EventData event) override;
};

#endif