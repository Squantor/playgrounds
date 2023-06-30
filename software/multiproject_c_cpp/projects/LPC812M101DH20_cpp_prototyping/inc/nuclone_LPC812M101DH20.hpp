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
#include <LPC8XX.hpp/LPC81X_gpio_regs.hpp>
#include <LPC8XX.hpp/LPC81X_gpio.hpp>

#define TICKS_PER_S 10

// Crystal osillator pins
using xtalInPinType = instances::pin<instances::IOports::PORT0, instances::IOpins::PIN08>;
using xtalOutPinType = instances::pin<instances::IOports::PORT0, instances::IOpins::PIN09>;
// test pin pair 0, connected to eachother via 1KOhm resistor
using test0PinType = instances::pin<instances::IOports::PORT0, instances::IOpins::PIN01>;
using test1PinType = instances::pin<instances::IOports::PORT0, instances::IOpins::PIN15>;
// auxillary test pin
using test2PinType = instances::pin<instances::IOports::PORT0, instances::IOpins::PIN07>;
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

void boardInit(void);
void ledState(bool isOn);

#endif