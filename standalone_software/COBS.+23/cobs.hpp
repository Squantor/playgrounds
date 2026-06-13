/**
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2026 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 *
 * @file cobs.hpp
 * @brief COBS encoder/decoder definitions
 */
#ifndef COBS_HPP
#define COBS_HPP

#include <cstdint>
#include <array>

/**
 * @brief COBS encoder/decoder
 */
class Cobs {
 public:
  /**
   * @brief COBS encoder/decoder constructor
   */
  Cobs() : index(0) {}
  /**
   * @brief Reset COBS encoder/decoder
   */
  void reset(void) {
    index = 0;
  }

 private:
  std::size_t index;
  std::array<std::uint8_t, 256> data;
};

#endif
