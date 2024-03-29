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

#define IOCON_XTAL_IN IOCON_PIO0_8
#define IOCON_XTAL_OUT IOCON_PIO0_9

#define IOCON_LED IOCON_PIO0_14
#define SWM_LED SWM_PORTPIN_P0_14
#define PORT_LED GPIO_PORT0
#define PIN_LED (14u)

#define IOCON_I2C_SCL IOCON_PIO0_10
#define SWM_I2C_SCL SWM_PORTPIN_P0_10
#define IOCON_I2C_SDA IOCON_PIO0_11
#define SWM_I2C_SDA SWM_PORTPIN_P0_11

#define TICKS_PER_S 2

void boardInit(void);

#endif