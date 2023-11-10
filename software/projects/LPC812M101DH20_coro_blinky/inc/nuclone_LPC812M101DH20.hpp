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
using gpioPort = libMcuLL::hw::port<libMcuLL::hw::IOports::PORT0>;

// Crystal osillator pins
using xtalInPinType = libMcuLL::hw::pin<libMcuLL::hw::IOports::PORT0, libMcuLL::hw::IOpins::PIN08>;
using xtalOutPinType = libMcuLL::hw::pin<libMcuLL::hw::IOports::PORT0, libMcuLL::hw::IOpins::PIN09>;
// LED pin
using LedPinType = libMcuLL::hw::pin<libMcuLL::hw::IOports::PORT0, libMcuLL::hw::IOpins::PIN14>;

// Peripheral functions
using xtalInFunctionType = libMcuLL::hw::swm::pinFunction<libMcuLL::hw::swm::pinFunctions::XTALIN>;
using xtalOutFunctionType = libMcuLL::hw::swm::pinFunction<libMcuLL::hw::swm::pinFunctions::XTALOUT>;

constexpr gpioPort mainPort;
constexpr xtalInPinType xtalInPin;
constexpr xtalOutPinType xtalOutPin;
constexpr LedPinType ledPin;

constexpr xtalInFunctionType xtalIn;
constexpr xtalOutFunctionType xtalOut;

extern libMcuLL::sw::iocon::iocon<libMcuLL::hw::IOCON_cpp> ioconPeripheral;
extern libMcuLL::sw::swm::swm<libMcuLL::hw::SWM_cpp> swmPeriperhal;
extern libMcuLL::sw::gpio::gpio<libMcuLL::hw::GPIO_cpp> gpioPeripheral;
extern libMcuLL::sw::syscon::syscon<libMcuLL::hw::SYSCON_cpp> sysconPeripheral;

#endif