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

template <size_t N>
struct peripheralSpi {
  std::array<uint16_t, N> transactionsTransmit;
  std::array<uint16_t, N> transactionsReceive;
};

enum spiOperations {
  CONT_TRANSCIEVE = 1,
  CONT_TRANSMIT = 2,
  CONT_RECEIVE = 3,
  END_TRANSCEIVE = 4,
  END_TRANSMIT = 5,
  END_RECEIVE = 6,
};

enum spiChipEnables {
  SPI_DEV_0 = 1,
  SPI_DEV_1 = 2,
  SPI_DEV_2 = 3,
  SPI_DEV_3 = 4,
};

template <auto &P>
class GenericSpi {
 public:
  GenericSpi() : transmitIndex{0}, receiveIndex{9} {}
  /**
   * @brief SPI transaction
   *
   * @param operation   SPI transaction to execute
   * @param device      SPI device
   * @param data        uint16_t buffer
   * @param bitCount    amount of bits to transfer, max of 8KiB
   */
  void transaction(spiOperations operation, spiChipEnables device, uint16_t *data, uint16_t bitCount) {
    uint16_t currentTransaction = device << 8 | operation;
    switch (operation) {
      case spiOperations::CONT_TRANSCIEVE:
        
        break;
      case spiOperations::CONT_TRANSMIT:
        break;
      case spiOperations::CONT_RECEIVE:
        break;
      case spiOperations::END_TRANSCEIVE:
        break;
      case spiOperations::END_TRANSMIT:
        break;
      case spiOperations::END_RECEIVE:
        break;
    }
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