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

template <size_t N>
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
    size_t dataElementCount = bitcount / 16 + 1;
    txTransactions[transmitIndex++] = bitcount;
    txTransactions[transmitIndex++] = static_cast<uint16_t>(device);
    txTransactions[transmitIndex++] = static_cast<uint16_t>(lastAction);
    for (size_t i = 0; i < dataElementCount; i++) {
      txTransactions[transmitIndex++] = transmitBuffer[i];
    }
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
   * @return size_t
   */
  int txTransactionCount(void) {
    size_t index = txTransactionNext(0);
    int transactionCount = 0;
    // iterate through transmit transactions
    while (index != 0) {
      transactionCount++;
      index = txTransactionNext(index);
      if (index == 0) {
        break;
      }
    }
    return transactionCount;
  }

  /**
   * @brief Get bit transfer count from transaction
   *
   * @param transaction transaction number,
   * @return uint16_t   transferred bits in transaction
   */
  uint16_t txTransactionGetBits(int transaction) {
    size_t index = txTransactionToIndex(transaction);
    return txTransactions[index];
  }

  /**
   * @brief get chip enable from transaction
   *
   * @param transaction transaction number
   * @return uint16_t   chip enable from transaction
   */
  uint16_t txTransactionGetChip(int transaction) {
    size_t index = txTransactionToIndex(transaction);
    return txTransactions[index + 1];
  }
  /**
   * @brief get last transmission indicator from transaction
   *
   * @param transaction transaction number
   * @return uint16_t   get last transmission indicator, 0 for not, non zero for last
   */
  uint16_t txTransactionGetLast(int transaction) {
    size_t index = txTransactionToIndex(transaction);
    return txTransactions[index + 2];
  }
  /**
   * @brief get data from transaction
   *
   * @param transaction transaction number
   * @return uint16_t*  pointer to first bits in uint16_t array
   */
  uint16_t* txTransactionGetData(int transaction) {
    size_t index = txTransactionToIndex(transaction);
    return &txTransactions[index + 3];
  }

 private:
  /**
   * @brief
   *
   * @param transaction
   * @return size_t
   */
  size_t txTransactionToIndex(int transaction) {
    size_t index = 0;
    int transactionCount = 1;
    // iterate through transmit transactions
    while (transactionCount < transaction) {
      index = txTransactionNext(index);
      if (index == 0)
        break;
      transactionCount++;
    }
    return index;
  }
  /**
   * @brief returns next transaction index
   *
   * @param index   input index
   * @return size_t index of next transaction, 0 for end or invalid
   */
  size_t txTransactionNext(size_t index) {
    if (txTransactions[index] == 0)
      return 0;
    size_t newIndex = index + (txTransactions[index] / 16) + 4;
    if (newIndex > N)
      return 0;
    return newIndex;
  }
  std::array<uint16_t, N> txTransactions;
  std::array<uint16_t, N> rxTransactions;
  size_t transmitIndex, receiveIndex;
};

}  // namespace sim_hw

#endif
