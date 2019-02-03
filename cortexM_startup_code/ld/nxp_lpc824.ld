/*
 * Unified Cortex Startup - GNU ld linker script file
 *
 * This file is in public domain
 *
 * Put together by Paul Sokolovsky
 *
 */

/* UM10600 Ch.2 p.9 */
MEMORY
{
    flash   :   ORIGIN = 0x00000000, LENGTH = 32K
    sram    :   ORIGIN = 0x10000000, LENGTH = 8K
}

/* Include main link script. Note: it will be searched in -L paths. */
INCLUDE linkscript_lpc.ld
