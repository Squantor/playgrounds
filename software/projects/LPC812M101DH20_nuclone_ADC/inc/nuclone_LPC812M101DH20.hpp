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
// Uart pins
using mainUartRxPinType = libMcuLL::hw::pin<libMcuLL::hw::IOports::PORT0, libMcuLL::hw::IOpins::PIN00>;
using mainUartTxPinType = libMcuLL::hw::pin<libMcuLL::hw::IOports::PORT0, libMcuLL::hw::IOpins::PIN04>;
// SPI pins
using mainSpiSckPinType = libMcuLL::hw::pin<libMcuLL::hw::IOports::PORT0, libMcuLL::hw::IOpins::PIN17>;
using mainSpiMisoPinType = libMcuLL::hw::pin<libMcuLL::hw::IOports::PORT0, libMcuLL::hw::IOpins::PIN13>;
using adcSpiCePinType = libMcuLL::hw::pin<libMcuLL::hw::IOports::PORT0, libMcuLL::hw::IOpins::PIN12>;

// Peripheral functions
using xtalInFunctionType = libMcuLL::hw::swm::pinFunction<libMcuLL::hw::swm::pinFunctions::XTALIN>;
using xtalOutFunctionType = libMcuLL::hw::swm::pinFunction<libMcuLL::hw::swm::pinFunctions::XTALOUT>;
using mainUartRxFunctionType = libMcuLL::hw::swm::pinFunction<libMcuLL::hw::swm::pinFunctions::U0_RXD_I>;
using mainUartTxFunctionType = libMcuLL::hw::swm::pinFunction<libMcuLL::hw::swm::pinFunctions::U0_TXD_O>;
using mainSpiSckFunctionType = libMcuLL::hw::swm::pinFunction<libMcuLL::hw::swm::pinFunctions::SPI0_SCK_IO>;
using mainSpiMisoFunctionType = libMcuLL::hw::swm::pinFunction<libMcuLL::hw::swm::pinFunctions::SPI0_MISO_IO>;
using adcSpiCeFunctionType = libMcuLL::hw::swm::pinFunction<libMcuLL::hw::swm::pinFunctions::SPI0_SSEL_IO>;

constexpr gpioPort mainPort;
constexpr xtalInPinType xtalInPin;
constexpr xtalOutPinType xtalOutPin;
constexpr mainUartRxPinType mainUartRxPin;
constexpr mainUartTxPinType mainUartTxPin;
constexpr mainSpiSckPinType mainSpiSckPin;
constexpr mainSpiMisoPinType mainSpiMisoPin;
constexpr adcSpiCePinType adcSpiCePin;

constexpr xtalInFunctionType xtalIn;
constexpr xtalOutFunctionType xtalOut;
constexpr mainUartRxFunctionType mainUartRxFunction;
constexpr mainUartTxFunctionType mainUartTxFunction;
constexpr mainSpiSckFunctionType mainSpiSckFunction;
constexpr mainSpiMisoFunctionType mainSpiMisoFunction;
constexpr adcSpiCeFunctionType adcSpiCeFunction;

extern libMcuLL::sw::iocon::iocon<libMcuLL::hw::IOCON_cpp> ioconPeripheral;
extern libMcuLL::sw::swm::swm<libMcuLL::hw::SWM_cpp> swmPeriperhal;
extern libMcuLL::sw::gpio::gpio<libMcuLL::hw::GPIO_cpp> gpioPeripheral;
extern libMcuLL::sw::syscon::syscon<libMcuLL::hw::SYSCON_cpp> sysconPeripheral;
extern libMcuLL::sw::spi::spiAsync<libMcuLL::hw::SPI0_cpp, libMcuLL::sw::spi::chipEnables, std::uint16_t> mainSpiPeripheral;
extern libMcuLL::sw::usart::usartAsync<libMcuLL::hw::USART0_cpp, std::uint8_t> mainUsartPeripheral;

extern libMcuLL::sw::spi::chipEnables adcChipEnable;

#endif