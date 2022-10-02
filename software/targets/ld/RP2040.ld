/*
SPDX-License-Identifier: MIT

Copyright (c) 2021 Bart Bilos
For conditions of distribution and use, see LICENSE file
*/

/*
Based on the excellent example by Alex Tadarov: 
https://github.com/ataradov/mcu-starter-projects/tree/master/rp2040
*/

MEMORY
{
    boot  :   ORIGIN = 0x10000000, LENGTH = 256
    rom   :   ORIGIN = 0x10000100, LENGTH = 2048K - 256
    ram   :   ORIGIN = 0x20000000, LENGTH = 264K
}

/* Include main link script. Note: it will be searched in -L paths. */
INCLUDE linkscript.ld
