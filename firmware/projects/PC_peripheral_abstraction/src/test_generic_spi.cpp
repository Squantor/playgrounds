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
#include <cstdio>
#include <MinUnit.h>
#include <board.hpp>

static void testGenericSpiSetup(minunitState* testResults) {
  board::testSpi0.initialize();
  minUnitPass();
}

static void testGenericSpiTeardown(minunitState* testResults) {
  minUnitPass();
}

MINUNIT_ADD(testGenericSpiTransmit, testGenericSpiSetup, testGenericSpiTeardown) {
  std::array<uint16_t, 10> testBuf{0x0123, 0x4567, 0x89ab, 0xcdef};
  board::testSpi0.transmit(sim_hw::spi::spiChipEnables::SPI_DEV_0, testBuf.data(), 5, true);
  minUnitCheck(1 == board::testSpi0.txTransactionCount());
  minUnitCheck(5 == board::testSpi0.txTransactionGetBits(1));
  minUnitCheck(static_cast<uint16_t>(sim_hw::spi::spiChipEnables::SPI_DEV_0) == board::testSpi0.txTransactionGetChip(1));
  minUnitCheck(0 != board::testSpi0.txTransactionGetLast(1));
  uint16_t* data = board::testSpi0.txTransactionGetData(1);
  minUnitCheck(0x0123 == *data);
  board::testSpi0.transmit(sim_hw::spi::spiChipEnables::SPI_DEV_1, testBuf.data(), 32, false);
  board::testSpi0.transmit(sim_hw::spi::spiChipEnables::SPI_DEV_1, testBuf.data(), 41, true);
  minUnitCheck(3 == board::testSpi0.txTransactionCount());
  minUnitCheck(32 == board::testSpi0.txTransactionGetBits(2));
  minUnitCheck(static_cast<uint16_t>(sim_hw::spi::spiChipEnables::SPI_DEV_1) == board::testSpi0.txTransactionGetChip(2));
  minUnitCheck(0 == board::testSpi0.txTransactionGetLast(2));
  data = board::testSpi0.txTransactionGetData(2);
  minUnitCheck(0x89AB == *(data + 2));
  minUnitCheck(41 == board::testSpi0.txTransactionGetBits(3));
  minUnitCheck(static_cast<uint16_t>(sim_hw::spi::spiChipEnables::SPI_DEV_1) == board::testSpi0.txTransactionGetChip(3));
  minUnitCheck(0 != board::testSpi0.txTransactionGetLast(3));
  data = board::testSpi0.txTransactionGetData(3);
  minUnitCheck(0x4567 == *(data + 1));
}