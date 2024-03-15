/*
SPDX-License-Identifier: MIT

Copyright (c) 2023 Bart Bilos
For conditions of distribution and use, see LICENSE file
*/
/**
 * @file driver for the MCP355X series ADC's
 */
#ifndef MCP355X_HPP
#define MCP355X_HPP

#include <sq_coro.hpp>
#include <cstdint>

template <typename T_spibus>
struct driverMCP355X {
  driverMCP355X(T_spibus& peripheral) : spibus(peripheral){};

  template <typename T_Check, typename T_disable>
  libMcuLL::results getSample(T_Check&& sampleAvailable, T_disable&& disableChip, std::uint32_t& raw, std::int32_t& sample) {
    CR_BEGIN(crCurrent);
    CR_WAIT(libMcuLL::results::BUSY, spibus.claim() == libMcuLL::results::CLAIMED);
    CR_WAIT(libMcuLL::results::BUSY, sampleAvailable() == 0);
    CR_WAIT(libMcuLL::results::BUSY,
            spibus.startRead(libMcuLL::sw::spi::chipEnables::SSEL_NONE, adcSampleOutput, 24, false) == libMcuLL::results::STARTED);
    CR_WAIT(libMcuLL::results::BUSY, spibus.progress() == libMcuLL::results::DONE);
    disableChip();
    raw = static_cast<uint32_t>(adcSampleOutput[0]) << 8;
    raw |= static_cast<uint32_t>(adcSampleOutput[1] & 0xFF);
    // ransform raw data and overflow conditions into a integer value
    if (raw & (1 << 22)) {
      sample = raw;
    } else if (raw & (1 << 23)) {
      sample = raw | 0xFFC00000;
    } else {
      if (raw & (1 << 21))
        sample = raw | 0xFFC00000;
      else
        sample = raw;
    }

    CR_YIELD(libMcuLL::results::DONE);
    CR_WAIT(libMcuLL::results::BUSY, spibus.unclaim() == libMcuLL::results::UNCLAIMED);
    CR_END(libMcuLL::results::BUSY);
  }
  T_spibus spibus;
  util::coroState crCurrent;
  std::array<std::uint16_t, 2> adcSampleOutput;
};

#endif