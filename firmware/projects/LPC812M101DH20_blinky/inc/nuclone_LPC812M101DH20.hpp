/*
SPDX-License-Identifier: MIT

Copyright (c) 2023 Bart Bilos
For conditions of distribution and use, see LICENSE file
*/
#ifndef NUCLONE_LPC812M101DH20_HPP
#define NUCLONE_LPC812M101DH20_HPP

#define CLOCK_MAIN_SOURCE SYSCTL_MAINCLKSRC_PLLOUT

#define CLOCK_XTAL (12000000u)
#define CLOCK_EXT_IN (0u)
#define CLOCK_CPU (30000000u)
#define CLOCK_AHB (30000000u)
#define CLOCK_MAIN (60000000u)

#include <mcu_ll.hpp>

#define TICKS_PER_S 10

// main gpio port
using gpioPort = instances::port<instances::IOports::PORT0>;

// Crystal osillator pins
using xtalInPinType = instances::pin<instances::IOports::PORT0, instances::IOpins::PIN08>;
using xtalOutPinType = instances::pin<instances::IOports::PORT0, instances::IOpins::PIN09>;
// LED pin
using LedPinType = instances::pin<instances::IOports::PORT0, instances::IOpins::PIN14>;

// Peripheral functions
using xtalInFunctionType = instances::swm::pinFunction<instances::swm::pinFunctions::XTALIN>;
using xtalOutFunctionType = instances::swm::pinFunction<instances::swm::pinFunctions::XTALOUT>;

constexpr gpioPort mainPort;
constexpr xtalInPinType xtalInPin;
constexpr xtalOutPinType xtalOutPin;
constexpr LedPinType ledPin;

constexpr xtalInFunctionType xtalIn;
constexpr xtalOutFunctionType xtalOut;

extern instances::iocon::iocon<peripherals::IOCON_cpp> ioconPeripheral;
extern instances::swm::swm<peripherals::SWM_cpp> swmPeriperhal;
extern instances::gpio::gpio<peripherals::GPIO_cpp> gpioPeripheral;
extern instances::syscon::syscon<peripherals::SYSCON_cpp> sysconPeripheral;

#endif