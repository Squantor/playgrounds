/*
 * SPDX-License-Identifier: MIT
 * Copyright (c) 2023 Bart Bilos
 *For conditions of distribution and use, see LICENSE file
 */
/**
 * \file board definitions
 */
#ifndef BOARD_HPP
#define BOARD_HPP

#include <sim_hw.hpp>

namespace board {
extern sim_hw::spiPeripheral<1000> testSpi0;
}

#endif
