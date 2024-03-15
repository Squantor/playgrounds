/*
 * SPDX-License-Identifier: MIT
 * Copyright (c) 2023 Bart Bilos
 *For conditions of distribution and use, see LICENSE file
 */
/**
 * \file board definitions
 */

#include <board.hpp>
#include <sim_hw.hpp>

namespace board {
sim_hw::spiPeripheral<1000> testSpi0;
}
