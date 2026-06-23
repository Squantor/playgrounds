/**
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2026 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 *
 * @file test_sim_rs485.cpp
 * @brief Simulated RS485 interface test definitions
 */
#include <array>
#include <span>
#include "minunit.h"
#include "sim_rs485.hpp"

namespace {
std::array<std::uint8_t, 32> bus_buffer;           //! common buffer size
std::array<Sim_rs485_state, 4> bus_states_buffer;  //! limited amount of interfaces

Sim_rs485 bus_dut(bus_buffer, bus_states_buffer);

MINUNIT_SETUP(test_sim_rs485_setup) {
  MINUNIT_PASS();
}

MINUNIT_TEARDOWN(test_sim_rs485_teardown) {
  MINUNIT_PASS();
}

MINUNIT_ADD(test_sim_rs485_constructor, test_sim_rs485_setup, test_sim_rs485_teardown) {
  MINUNIT_PASS();
}

}  // namespace
