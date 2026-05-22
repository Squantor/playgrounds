/**
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2026 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 *
 * @file menu_item.hpp
 * @brief Menu screen item definition
 *
 */
#ifndef MENU_ITEM_HPP
#define MENU_ITEM_HPP

class Menu_item {
 public:
  Menu_item(const char *menu_item_name) : name(menu_item_name) {}
  // button handler for increment/modify value
  // get menu item string
  const char *get_name() {
    return name;
  }

 private:
  const char *name;
};

#endif