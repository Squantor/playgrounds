/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2023 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 * \brief general purpose peripheral tests
 *
 * Simple template based abstraction test
 */
#include <array>
#include <cstdio>
#include <cstdint>
#include <MinUnit.h>

enum class spiChipEnables : uint16_t {
  SPI_DEV_0 = 1,
  SPI_DEV_1 = 2,
  SPI_DEV_2 = 3,
  SPI_DEV_3 = 4,
};

template <size_t N>
struct peripheralSpi {
  std::array<uint16_t, N> transactionsTransmit;
  std::array<uint16_t, N> transactionsReceive;
  // Method to add a receive transaction
  // Method that returns transmit transactions
  // Method that returns receive transactions
};

template <auto& P>
class GenericSpi {
 public:
  GenericSpi() : transmitIndex{0}, receiveIndex{9} {}
  void transmit(spiChipEnables device, const uint16_t* transmitBuffer, uint16_t bitcount, bool lastAction) {
    // Put transaction data into transactionsTransmit
    // compute index count
    // put bit data in transactionsTransmit
  }
  void receive(spiChipEnables device, uint16_t* receiveBuffer, uint16_t bitcount, bool lastAction) {
    // assert if we have no data for this device, should be filled in the transactionsReceive
    // Put transaction data into transactionsReceive
    // compute index count
    // copy data in receive buffer
  }
  void transceive(spiChipEnables device, const uint16_t* transmitBuffer, uint16_t* receiveBuffer, uint16_t bitcount,
                  bool lastAction) {
    // assert if we have no data for this device, should be filled in the transactionsReceive
    // Put transaction data into transactionsReceive
    // compute index count for transmit and receive
    // copy data from transactionsReceive in receive buffer
    // put transmit buffer data in transactionsTransmit
  }

 private:
  size_t transmitIndex, receiveIndex;
};

/*
template <auto &P>
class deviceGeneric {
 public:
  uint32_t doSomething(uint16_t value) {
    return P.transceive(value, 8);
  }

 private:
};
*/

peripheralSpi<100> testSpiHardware;
GenericSpi<testSpiHardware> testSpi;
// deviceGeneric<testSpi> testDevice;

MINUNIT_ADD(testGenericSpi, NULL, NULL) {
  // uint32_t value = testDevice.doSomething(10);
  minUnitCheck(18u == 18u);
}