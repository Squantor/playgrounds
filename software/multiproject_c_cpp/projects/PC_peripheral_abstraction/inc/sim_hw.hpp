/*
 * SPDX-License-Identifier: MIT
 * Copyright (c) 2023 Bart Bilos
 *For conditions of distribution and use, see LICENSE file
 */
/**
 * \file simulated hardware definitions
 */
#ifndef SIM_HW_HPP
#define SIM_HW_HPP

#include <cstddef>
#include <cstdint>
#include <array>

namespace sim_hw {
namespace spi {
enum class spiChipEnables : uint16_t {
  SPI_DEV_0 = 1,
  SPI_DEV_1 = 2,
  SPI_DEV_2 = 3,
  SPI_DEV_3 = 4,
};
}  // namespace spi

class spiPeripheral {
 public:
  spiPeripheral() : transmitIndex{0}, receiveIndex{0} {}
  /**
   * @brief clears this simulated SPI peripheral
   *
   */
  void initialize(void) {
    for (auto& data : txTransactions)
      data = 0;
    for (auto& data : rxTransactions)
      data = 0;
  }
  void transmit(sim_hw::spi::spiChipEnables device, const uint16_t* transmitBuffer, uint16_t bitcount, bool lastAction) {
    // Put transaction data into transactionsTransmit
    // compute index count
    // put bit data in transactionsTransmit
  }
  void receive(sim_hw::spi::spiChipEnables device, uint16_t* receiveBuffer, uint16_t bitcount, bool lastAction) {
    // assert if we have no data for this device, should be filled in the transactionsReceive
    // Put transaction data into transactionsReceive
    // compute index count
    // copy data in receive buffer
  }
  void transceive(sim_hw::spi::spiChipEnables device, const uint16_t* transmitBuffer, uint16_t* receiveBuffer, uint16_t bitcount,
                  bool lastAction) {
    // assert if we have no data for this device, should be filled in the transactionsReceive
    // Put transaction data into transactionsReceive
    // compute index count for transmit and receive
    // copy data from transactionsReceive in receive buffer
    // put transmit buffer data in transactionsTransmit
  }
  /**
   * @brief Return amount of transmit transactions
   *
   * @return int
   */
  int txCount(void) {
    // iterate through transmit transactions
  }
  // TODO get transaction X data count
  // TODO get transaction X chip enable
  // TODO get transaction X data pointer

 private:
  std::array<uint16_t, 100> txTransactions;
  std::array<uint16_t, 100> rxTransactions;
  size_t transmitIndex, receiveIndex;
};

}  // namespace sim_hw

#endif
