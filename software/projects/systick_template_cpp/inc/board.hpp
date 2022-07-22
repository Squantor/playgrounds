/*
SPDX-License-Identifier: MIT

Copyright (c) 2021 Bart Bilos
For conditions of distribution and use, see LICENSE file
*/
#ifndef BOARD_HPP
#define BOARD_HPP

#define CLOCK_MAIN_SOURCE SYSCTL_MAINCLKSRC_IRC

#define CLOCK_XTAL (12000000u)
#define CLOCK_EXT_IN (0u)
#define CLOCK_CPU (12000000u)
#define CLOCK_AHB (12000000u)
#define CLOCK_MAIN (12000000u)

#include <mcu_ll.h>

#define TICKS_PER_S 1

void boardInit(void);

#endif
