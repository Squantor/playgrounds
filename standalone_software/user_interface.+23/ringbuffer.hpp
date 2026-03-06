/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2021 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 * @file ringbuffer.hpp
 * @brief Implements a generic ringbuffer class
 */
#ifndef RINGBUFFER_HPP
#define RINGBUFFER_HPP

#include <array>
#include <cstdint>

/**
 * @brief Ringbuffer class
 * @tparam T Type to be used in the ringbuffer
 * @tparam N Amount of elements in the ringbuffer
 */
template <typename T, std::size_t size>
class Ringbuffer {
 public:
  using iterator = typename std::array<T, size>::iterator;
  /**
   * @brief Construct a new Ring Buffer object
   */
  Ringbuffer() {
    static_assert(size > 0, "ringbuffer size of zero is not allowed!");
    reset();
  }
  /**
   * @brief Resets the ringbuffer
   */
  void reset() {
    front = buffer.begin();
    back = buffer.begin();
  }
  /**
   * @brief Checks if the ringbuffer is full
   * @return true if ringbuffer is full
   * @return false if ringbuffer is not full
   */
  bool is_full() {
    return increment(front) == back;
  }
  /**
   * @brief Checks if the ringbuffer is empty
   * @return true if ringbuffer is empty
   * @return false if ringbuffer is not empty
   */
  bool is_empty() const {
    return front == back;
  }
  /**
   * @brief returns fill level of the ringbuffer
   * @return amount of elements in ringbuffer
   */
  std::size_t get_level() {
    if (front > back)
      return front - back;
    if (back > front)
      return size - (back - front);
    else
      return 0;
  }
  /**
   * @brief Pushes a value to the back of the ringbuffer
   * @param p Element to push
   * @return true if push was successful
   * @return false if buffer was full
   */
  bool push_back(const T &p) {
    if (is_full())
      return false;
    auto temp = decrement(back);
    back = temp;
    *back = p;
    return true;
  }
  /**
   * @brief Pushes a value to the front of the ringbuffer
   * @param p Element to push
   * @return true if push was successful
   * @return false if buffer was full
   */
  bool push_front(const T &p) {
    if (is_full())
      return false;
    auto temp = increment(front);
    *front = p;
    front = temp;
    return true;
  }
  /**
   * @brief Pops a value from the back of the ringbuffer
   * @param p Element to pop into
   * @return true if pop was successful
   * @return false if buffer was empty
   */
  bool pop_back(T &p) {
    if (is_empty())
      return false;
    auto temp = increment(back);
    p = *back;
    back = temp;
    return true;
  }
  /**
   * @brief Pops a value from the front of the ringbuffer
   * @return true if pop was successful
   * @return false if buffer was empty
   */
  bool pop_back() {
    if (is_empty())
      return false;
    back = increment(back);
    return true;
  }
  /**
   * @brief Pops a value from the front of the ringbuffer
   * @param p Element to pop into
   * @return true if pop was successful
   * @return false if buffer was empty
   */
  bool pop_front(T &p) {
    if (is_empty())
      return false;
    auto temp = decrement(front);
    p = *temp;
    front = temp;
    return true;
  }
  /**
   * @brief Pops a value from the front of the ringbuffer
   * @return true if pop was successful
   * @return false if buffer was empty
   */
  bool pop_front(void) {
    if (is_empty())
      return false;
    front = decrement(front);
    return true;
  }

 private:
  /**
   * @brief decrements the iterator
   * @param p iterator to decrement
   * @return decremented iterator taking care of wraparound
   */
  iterator decrement(const iterator p) {
    if (p == buffer.begin())
      return buffer.end() - 1;
    else
      return p - 1;
  }
  /**
   * @brief increments the iterator
   * @param p interator to increment
   * @return incremented iterator taking care of wraparound
   */
  iterator increment(const iterator p) {
    if (p + 1 == buffer.end())
      return buffer.begin();
    else
      return p + 1;
  }

  iterator front;                 /*!< first element of the ringbuffer */
  iterator back;                  /*!< last element of the ringbuffer */
  std::array<T, size + 1> buffer; /*!< ringbuffer data, one element is added as
                                     we need always one element free */
};

#endif
