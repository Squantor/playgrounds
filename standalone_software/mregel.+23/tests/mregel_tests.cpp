/**
 *SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2025 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 * @file main.cpp
 * @brief Main entrypoint for executing minunit tests
 */
#include "minunit.h"
#include "mregel.hpp"
#include <cstring>

std::array<char, 12> hello_world = {'H', 'e', 'l', 'l', 'o', ' ', 'W', 'o', 'r', 'l', 'd', '!'};
std::array<char, 15> test_array;

MINUNIT_ADD(mregel_test_size, nullptr, nullptr) {
  mregel mregel_empty;
  MINUNIT_CHECK(mregel_empty.size() == 0);
  MINUNIT_CHECK(mregel_empty.data() == nullptr);
  mregel mregel_non_empty{test_array};
  MINUNIT_CHECK(mregel_non_empty.size() == 0);
  MINUNIT_ASSERT(mregel_non_empty.data() == test_array.data());
  MINUNIT_CHECK(mregel_non_empty.data_size() == 14);
  mregel_non_empty.add("");
  MINUNIT_CHECK(mregel_non_empty.size() == 0);
  mregel_non_empty.add("Hello");
  MINUNIT_CHECK(mregel_non_empty.size() == 5);
  mregel_non_empty.add(" World");
  MINUNIT_CHECK(mregel_non_empty.size() == 11);
  mregel_non_empty.add("!");
  MINUNIT_CHECK(mregel_non_empty.size() == 12);
  MINUNIT_CHECK(strcmp(mregel_non_empty.c_str(), "Hello World!") == 0);
  std::span mregel_span = mregel_non_empty.span();
  MINUNIT_CHECK(mregel_span.size() == 12);
  MINUNIT_CHECK(memcmp(mregel_span.data(), hello_world.data(), 12) == 0);
}