/*
SPDX-License-Identifier: MIT

Copyright (c) 2021 Bart Bilos
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

#include <LPC8XX.hpp/LPC81X_acmp_regs.hpp>
#include <LPC8XX.hpp/LPC81X_crc_regs.hpp>
#include <LPC8XX.hpp/LPC81X_fmc_regs.hpp>
#include <LPC8XX.hpp/LPC81X_i2c_regs.hpp>
#include <LPC8XX.hpp/LPC81X_mrt_regs.hpp>
#include <LPC8XX.hpp/LPC81X_pin_int_regs.hpp>
#include <LPC8XX.hpp/LPC81X_pmu_regs.hpp>
#include <LPC8XX.hpp/LPC81X_sct_regs.hpp>
#include <LPC8XX.hpp/LPC81X_syscon_regs.hpp>
#include <LPC8XX.hpp/LPC81X_usart_regs.hpp>
#include <LPC8XX.hpp/LPC81X_wkt_regs.hpp>
#include <LPC8XX.hpp/LPC81X_wwdt_regs.hpp>

#include <LPC8XX.hpp/LPC81X_acmp.hpp>
#include <LPC8XX.hpp/LPC81X_crc.hpp>
#include <LPC8XX.hpp/LPC81X_fmc.hpp>
#include <LPC8XX.hpp/LPC81X_i2c.hpp>
#include <LPC8XX.hpp/LPC81X_mrt.hpp>
#include <LPC8XX.hpp/LPC81X_pin_int.hpp>
#include <LPC8XX.hpp/LPC81X_pmu.hpp>
#include <LPC8XX.hpp/LPC81X_sct.hpp>
#include <LPC8XX.hpp/LPC81X_syscon.hpp>
#include <LPC8XX.hpp/LPC81X_usart.hpp>
#include <LPC8XX.hpp/LPC81X_wkt.hpp>
#include <LPC8XX.hpp/LPC81X_wwdt.hpp>

#define TICKS_PER_S 10

// main gpio port
using gpioPort = instances::port<instances::IOports::PORT0>;

// Crystal osillator pins
using xtalInPinType = instances::pin<instances::IOports::PORT0, instances::IOpins::PIN08>;
using xtalOutPinType = instances::pin<instances::IOports::PORT0, instances::IOpins::PIN09>;
// test pin pair 0, connected to eachother via 1KOhm resistor
using test0PinType = instances::pin<instances::IOports::PORT0, instances::IOpins::PIN01>;
using test1PinType = instances::pin<instances::IOports::PORT0, instances::IOpins::PIN15>;
// auxillary test pin, connected to nothing
using test2PinType = instances::pin<instances::IOports::PORT0, instances::IOpins::PIN07>;
using test3PinType = instances::pin<instances::IOports::PORT0, instances::IOpins::PIN14>;
// I2C Clock pin pair, pulled up to 2.2K to 3.3V
using i2cSclOutPinType = instances::pin<instances::IOports::PORT0, instances::IOpins::PIN10>;
using i2cSclSensePinType = instances::pin<instances::IOports::PORT0, instances::IOpins::PIN16>;
// I2C Data pin pair, pulled up to 2.2K to 3.3V
using i2cSdaOutPinType = instances::pin<instances::IOports::PORT0, instances::IOpins::PIN11>;
using i2cSdaSensePinType = instances::pin<instances::IOports::PORT0, instances::IOpins::PIN04>;

// Peripheral functions
using mainI2cSdaFunctionType = instances::swm::pinFunction<instances::swm::pinFunctions::I2C_SDA_IO>;
using mainI2cSclFunctionType = instances::swm::pinFunction<instances::swm::pinFunctions::I2C_SCL_IO>;
using xtalInFunctionType = instances::swm::pinFunction<instances::swm::pinFunctions::XTALIN>;
using xtalOutFunctionType = instances::swm::pinFunction<instances::swm::pinFunctions::XTALOUT>;
using mainSpiSckFunctionType = instances::swm::pinFunction<instances::swm::pinFunctions::SPI0_SCK_IO>;
using mainSpiSselFunctionType = instances::swm::pinFunction<instances::swm::pinFunctions::SPI0_SSEL_IO>;
using mainSpiMosiFunctionType = instances::swm::pinFunction<instances::swm::pinFunctions::SPI0_MOSI_IO>;
using mainSpiMisoFunctionType = instances::swm::pinFunction<instances::swm::pinFunctions::SPI0_MISO_IO>;

constexpr xtalInPinType xtalInPin;
constexpr xtalOutPinType xtalOutPin;
constexpr test0PinType test0Pin;
constexpr test1PinType test1Pin;
constexpr test2PinType test2Pin;
constexpr test3PinType test3Pin;
constexpr i2cSclOutPinType i2cSclOutPin;
constexpr i2cSdaOutPinType i2cSdaOutPin;
constexpr i2cSclSensePinType i2cSclSensePin;
constexpr i2cSdaSensePinType i2cSdaSensePin;
constexpr gpioPort mainPort;

constexpr mainI2cSclFunctionType i2cMainSclFunction;
constexpr mainI2cSdaFunctionType i2cMainSdaFunction;
constexpr mainSpiSckFunctionType spiMainSckFunction;
constexpr mainSpiSselFunctionType spiMainSselFunction;
constexpr mainSpiMosiFunctionType spiMainMosiFunction;
constexpr mainSpiMisoFunctionType spiMainMisoFunction;
constexpr xtalInFunctionType xtalIn;
constexpr xtalOutFunctionType xtalOut;

extern instances::gpio::gpio<peripherals::GPIO_cpp> gpioPeripheral;
extern instances::spi::spi<peripherals::SPI0_cpp> spiPeripheral;

void boardInit(void);

#endif