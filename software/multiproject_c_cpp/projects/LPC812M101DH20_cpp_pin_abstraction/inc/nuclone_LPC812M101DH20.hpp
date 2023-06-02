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

#include <mcu_ll.h>
#include <LPC812M101DH20.hpp>

#define TICKS_PER_S 10

#define IOCON_XTAL_IN IOCON_PIO0_8
#define IOCON_XTAL_OUT IOCON_PIO0_9

// test pin pair 0, connected to eachother via 1KOhm resistor
#define IOCON_TESTPIN_0_0 (IOCON_PIO0_1)
#define PORT_TESTPIN_0_0 (GPIO_PORT0)
#define PIN_TESTPIN_0_0 (1u)
#define SWM_TESTPIN_0_0 (SWM_PORTPIN_P0_1)
#define IOCON_TESTPIN_0_1 (IOCON_PIO0_15)
#define PORT_TESTPIN_0_1 (GPIO_PORT0)
#define PIN_TESTPIN_0_1 (15u)
#define SWM_TESTPIN_0_1 (SWM_PORTPIN_P0_15)

// I2C Clock test pin, pulled up to 2.2K to 3.3V
#define IOCON_I2C_SCL_OUT (IOCON_PIO0_10)
#define PORT_I2C_SCL_OUT (GPIO_PORT0)
#define PIN_I2C_SCL_OUT (10u)
#define SWM_I2C_SCL_OUT (SWM_PORTPIN_P0_10)
#define IOCON_I2C_SCL_TEST (IOCON_PIO0_16)
#define PORT_I2C_SCL_TEST (GPIO_PORT0)
#define PIN_I2C_SCL_TEST (16u)
#define SWM_I2C_SCL_TEST (SWM_PORTPIN_P0_16)
// I2C Data test pin, pulled up to 2.2K to 3.3V
#define IOCON_I2C_SDA_OUT (IOCON_PIO0_11)
#define PORT_I2C_SDA_OUT (GPIO_PORT0)
#define PIN_I2C_SDA_OUT (11u)
#define SWM_I2C_SDA_OUT (SWM_PORTPIN_P0_11)
#define IOCON_I2C_SDA_TEST (IOCON_PIO0_4)
#define PORT_I2C_SDA_TEST (GPIO_PORT0)
#define PIN_I2C_SDA_TEST (4u)
#define SWM_I2C_SDA_TEST (SWM_PORTPIN_P0_4)

// loose test IOpins
#define IOCON_TESTPIN_2 (IOCON_PIO0_7)
#define PORT_TESTPIN_2 (GPIO_PORT0)
#define PIN_TESTPIN_2 (7u)
#define SWM_TESTPIN_2 (SWM_PORTPIN_P0_7)

using xtalInType = instances::pin<instances::IOports::PORT0, instances::IOpins::PIN08>;
using xtalOutType = instances::pin<instances::IOports::PORT0, instances::IOpins::PIN09>;
using testPin0Type = instances::pin<instances::IOports::PORT0, instances::IOpins::PIN01>;
using testPin1Type = instances::pin<instances::IOports::PORT0, instances::IOpins::PIN15>;
using testPin2Type = instances::pin<instances::IOports::PORT0, instances::IOpins::PIN07>;
using i2cSclOutType = instances::pin<instances::IOports::PORT0, instances::IOpins::PIN10>;
using i2cSclSenseType = instances::pin<instances::IOports::PORT0, instances::IOpins::PIN16>;
using i2cSdaOutType = instances::pin<instances::IOports::PORT0, instances::IOpins::PIN11>;
using i2cSdaSenseType = instances::pin<instances::IOports::PORT0, instances::IOpins::PIN04>;

void boardInit(void);
void ledState(bool isOn);

#endif