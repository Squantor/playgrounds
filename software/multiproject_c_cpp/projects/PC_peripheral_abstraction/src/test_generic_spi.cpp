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

static void testGenericSpiSetup(minunitState* state) {
  board::testSpi0.initialize();
}

static void testGenericSpiTeardown(minunitState* state) {}

MINUNIT_ADD(testGenericSpi, testGenericSpiSetup, testGenericSpiTeardown) {
  std::array<uint16_t, 10> testBuf;
  // uint32_t value = testDevice.doSomething(10);
  board::testSpi0.transmit(sim_hw::spi::spiChipEnables::SPI_DEV_0, testBuf.data(), 5, true);
  minUnitCheck(18u == 18u);
}