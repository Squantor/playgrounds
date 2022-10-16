/*
SPDX-License-Identifier: MIT

Copyright (c) 2021 Bart Bilos
For conditions of distribution and use, see LICENSE file
*/
/**
@file RP2040 startup code, based on the template by Alex Taradov:
https://github.com/ataradov/mcu-starter-projects/tree/master/rp2040
*/

#include <stdint.h>
#include <mcu_ll.h>

extern int main(void);

#if defined(__cplusplus)
extern "C" {
#endif

/* Linker symbols that are used to prepare the C/C++ environment */
extern uint32_t _data_flash;
extern uint32_t _start_data;
extern uint32_t _end_data;
extern uint32_t _start_bss;
extern uint32_t _end_bss;
extern void _end_stack(void);
extern void (*__preinit_array_start[])(void);
extern void (*__preinit_array_end[])(void);
extern void (*__init_array_start[])(void);
extern void (*__init_array_end[])(void);

void Reset_Handler(void);

#if defined(__cplusplus)
}  // extern "C"
#endif

/**
 * @brief
 *
 * This code must be position independent, it is linked at 0x10000000, but loaded at 0x20041f00.
 */
__attribute__((naked, used, noreturn, section(".boot.entry"))) void Reset_Handler(void) {
  // setup XIP SSI peripheral

  XIP_SSI->SSIENR = 0;
  XIP_SSI->BAUDR = 2;  // Must be even

  XIP_SSI->CTRLR0 = (XIP_SSI_CTRLR0_SPI_FRF_STD << XIP_SSI_CTRLR0_SPI_FRF_Pos) |
                    (XIP_SSI_CTRLR0_TMOD_EEPROM_READ << XIP_SSI_CTRLR0_TMOD_Pos) | ((32 - 1) << XIP_SSI_CTRLR0_DFS_32_Pos);

  XIP_SSI->SPI_CTRLR0 = (0x03 /*READ_DATA*/ << XIP_SSI_SPI_CTRLR0_XIP_CMD_Pos) | ((24 / 4) << XIP_SSI_SPI_CTRLR0_ADDR_L_Pos) |
                        (XIP_SSI_SPI_CTRLR0_INST_L_8B << XIP_SSI_SPI_CTRLR0_INST_L_Pos) |
                        (XIP_SSI_SPI_CTRLR0_TRANS_TYPE_1C1A << XIP_SSI_SPI_CTRLR0_TRANS_TYPE_Pos);

  XIP_SSI->SSIENR = XIP_SSI_SSIENR_SSI_EN_Msk;

  uint32_t *src, *dst;
  //

  // Old stuff below!!!
  /* Copy data section from flash to RAM */
  src = &_data_flash;
  dst = &_start_data;
  while (dst < &_end_data) *dst++ = *src++;

  /* Clear the bss section*/
  dst = &_start_bss;
  while (dst < &_end_bss) *dst++ = 0;

  /* execute c++ constructors */
  auto preInitFunc = __preinit_array_start;
  while (preInitFunc < __preinit_array_end) {
    (*preInitFunc)();
    preInitFunc++;
  }
  auto initFunc = __init_array_start;
  while (initFunc < __init_array_end) {
    (*initFunc)();
    initFunc++;
  }

  main();

  /* we omit executing destructors so gcc can optimize them away*/

  while (1)
    ;
}
