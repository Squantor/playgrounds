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

/* We define some clock definitions here to silence a warning */
#define CLOCK_XTAL (12000000u)
#define CLOCK_CPU (12000000u)

#include <mcu_ll.h>

extern int main(void);

#if defined(__cplusplus)
extern "C" {
#endif

// vector table
extern void (*const core_vector_table[16])(void);
// linker symbols used to prepare C/C++ environment
extern uint32_t _rom_start;
extern uint32_t _text_start;
extern uint32_t _text_end;
extern uint32_t _data_start;
extern uint32_t _data_end;
extern uint32_t _bss_start;
extern uint32_t _bss_end;
extern uint32_t _stack_top;
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
 * @brief Reset handler
 *
 * This code must be position independent, it is linked at 0x10000000, but loaded at 0x20041f00.
 */
__attribute__((naked, used, noreturn, section(".boot.entry"))) void Reset_Handler(void) {
  // setup XIP SSI peripheral
  xipssiEnable(XIP_SSI, false);
  xipssiBaudrate(XIP_SSI, 2);  // Must be even (BABI: Why then? TODO investigate)
  xipssiCtrlr0(XIP_SSI, XIP_SSI_CTRLR0_TMOD(XIP_SSI_CTRL0_TMOD_EEPROM) | XIP_SSI_CTRLR0_DFS_32(32 - 1) |
                          XIP_SSI_CTRLR0_SPI_FRF(XIP_SSI_CTRL0_SPI_FRF_1BIT));
  xipssiCtrlr1(XIP_SSI, XIP_SSI_CTRLR1_NDF(0));
  xipssiSpictrl0(XIP_SSI, XIP_SSI_SPI_CTRLR0_SPI_XIP_CMD(0x03) | XIP_SSI_SPI_CTRLR0_ADDR_L(24 / 4) |
                            XIP_SSI_SPI_CTRLR0_INST_L(XIP_SSI_SPI_CTRLR0_INST_L_8B_INSTR) |
                            XIP_SSI_SPI_CTRLR0_TRANS_TYPE(XIP_SSI_SPI_CTRLR0_TRANS_TYPE_STD_BOTH));
  xipssiEnable(XIP_SSI, true);

  uint32_t *src, *dst;
  // Copy flash to RAM based sections .text and .data
  // we copy everything in one go starting at _text_start until _data_end
  src = &_rom_start;
  dst = &_text_start;
  while (dst < &_data_end) *dst++ = *src++;
  // zero out bss
  dst = &_bss_start;
  while (dst < &_bss_end) *dst++ = 0;

  // execute C++ constructors
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

  SCB->VTOR = reinterpret_cast<uint32_t>(core_vector_table);

  asm(R"asm(
    msr    msp, %[sp]
    bx     %[reset]
    )asm" ::[sp] "r"(&_stack_top),
      [reset] "r"(main));

  __builtin_unreachable();
}
