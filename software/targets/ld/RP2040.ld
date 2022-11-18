/*
SPDX-License-Identifier: MIT

Copyright (c) 2021 Bart Bilos
For conditions of distribution and use, see LICENSE file
*/

/*
RP2040 linkerfile code, inspired by the template by Alex Taradov:
https://github.com/ataradov/mcu-starter-projects/tree/master/rp2040
More information taken from raspberry Pi Pico SDK
*/

MEMORY
{
  rom  (rx) : ORIGIN = 0x10000000, LENGTH = 2048K
  ram (rwx) : ORIGIN = 0x20000000, LENGTH = 256K
  core0Stack (rwx) : ORIGIN = 0x20040000, LENGTH = 4k
  core1Stack (rwx) : ORIGIN = 0x20041000, LENGTH = 4k
}

/* Include main link script. Note: it will be searched in -L paths. */
INCLUDE linkscript_rp2040.ld
