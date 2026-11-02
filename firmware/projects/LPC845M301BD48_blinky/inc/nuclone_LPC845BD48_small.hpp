/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2024 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 * @brief definitions for LPC845 small nucloner
 */
#ifndef NUCLONE_LPC845BD48_SMALL_HPP
#define NUCLONE_LPC845BD48_SMALL_HPP

#define CLOCK_XTAL (12'000'000u)
#define CLOCK_EXT_IN (0u)
#define CLOCK_CPU (30'000'000u)
#define CLOCK_AHB (30'000'000u)
#define CLOCK_MAIN (60'000'000u)

#include <nxp/libmcu_LPC845M301BD48_hal.hpp>

#define TICKS_PER_S 10

// pin types
// Crystal osillator pins
using xtalInPinType = libmcuhw::pin<libmcuhw::IOports::PORT0, libmcuhw::IOpins::PIN08>;
using xtalOutPinType = libmcuhw::pin<libmcuhw::IOports::PORT0, libmcuhw::IOpins::PIN09>;
using testPinType = libmcuhw::pin<libmcuhw::IOports::PORT1, libmcuhw::IOpins::PIN05>;
using ledPinType = libmcuhw::pin<libmcuhw::IOports::PORT1, libmcuhw::IOpins::PIN04>;

// function types
using xtalInFunctionType = libmcuhw::swm::PinFunction<libmcuhw::swm::PinFunctions::XTALIN>;
using xtalOutFunctionType = libmcuhw::swm::PinFunction<libmcuhw::swm::PinFunctions::XTALOUT>;
using clockOutFunctionType = libmcuhw::swm::PinFunction<libmcuhw::swm::PinFunctions::CLKOUT_O>;

// pin instances
constexpr xtalInPinType xtalInPin;
constexpr xtalOutPinType xtalOutPin;
constexpr testPinType testPin;
constexpr ledPinType ledPin;

// function instances
constexpr xtalInFunctionType xtalInFunction;
constexpr xtalOutFunctionType xtalOutFunction;
constexpr clockOutFunctionType clockOutFunction;

// peripheral externs
extern libmcull::iocon::Iocon<libmcuhw::IoconAddress> ioconPeripheral;
extern libmcull::swm::Swm<libmcuhw::SwmAddress> swmPeriperhal;
extern libmcull::gpio::Gpio<libmcuhw::GpioAddress> gpioPeripheral;
extern libmcull::syscon::Syscon<libmcuhw::SysconAddress> sysconPeripheral;
extern libmcull::systick::Systick<libmcuhw::systick_address> systickPeripheral;

void boardInit(void);

#endif