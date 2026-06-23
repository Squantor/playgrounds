/**
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2026 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 *
 * @file sim_rs485.hpp
 * @brief Simulated RS485 interface declarations
 * This is a simulated RS485 interface for testing various protocols running 
 * on this bus. 
 * @todo implementation
 * @todo bit error injection
 * @todo frame error injection
 * @todo dropped byte injection
 */
#ifndef SIM_RS485_HPP
#define SIM_RS485_HPP

#include <cstdint>
#include <span>

struct Sim_rs485_state
{
    std::size_t bus_data_tail;
};

/**
 * @brief Simulated RS485 interface class declaration
 * 
 */
class Sim_rs485 {
    public:
    /**
     * @brief Construct a new Sim_rs485 object
     * @param bus_buffer Bus buffer used for transmission and reception
     * @param bus_states_buffer Bus interface states for all the buses
     */
    Sim_rs485(std::span<std::uint8_t> bus_buffer, std::span<Sim_rs485_state> bus_states_buffer) : bus_data(bus_buffer), bus_states(bus_states_buffer) {}
    //! @todo implement reset
    //! @todo implement bus reset
    //! @todo implement write block to bus
    //! @todo implement read block from bus
    private:
    std::size_t bus_data_head;
    std::span<std::uint8_t> bus_data;
    std::span<Sim_rs485_state> bus_states;
};

#endif