/**
 *SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2025 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 * @file mregel.hpp
 * @brief mregel class definitions
 */
#ifndef MREGEL_HPP
#define MREGEL_HPP
#include <cstdint>
#include <span>

/**
 * @brief
 */
class mregel {
 public:
  /**
   * @brief Default empty constructor
   */
  mregel() : mregel_data(std::span<char>()), mregel_data_size(0) {}
  mregel(std::span<char> data) : mregel_data(data), mregel_data_size(0) {}
  // constructor for initializing the span
  /**
   * @brief Return size of mregel
   * @return size in characters
   */
  constexpr std::size_t size() const noexcept {
    return mregel_data_size;
  }
  /**
   * @brief Return underlying size of mregel
   * @return available space
   */
  constexpr std::size_t data_size() const noexcept {
    if (mregel_data.size() == 0) {
      return 0;
    }
    return mregel_data.size() - 1;
  }
  /**
   * @brief Return pointer to mregel data store
   * @return char pointer to mregel data store
   */
  constexpr char* data() const noexcept {
    return mregel_data.data();
  }
  /**
   * @brief Return pointer to mregel data store formatted to a c string
   * @return pointer to c string
   */
  const char* c_str() const noexcept {
    for (size_t i = mregel_data_size; i < mregel_data.size(); i++) {
      mregel_data[i] = '\0';
    }
    return mregel_data.data();
  }
  /**
   * @brief Add C string to mregel
   * @note will copy up to mregel_data.size()
   * @param c_str C string
   */
  void add(const char* c_str) {
    while (*c_str != '\0' && mregel_data_size < mregel_data.size()) {
      mregel_data[mregel_data_size] = *c_str;
      mregel_data_size++;
      c_str++;
    }
  }

 private:
  std::span<char> mregel_data;
  std::size_t mregel_data_size;
};

#endif