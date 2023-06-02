/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2023 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 * \file LPC810 series SWM register interface
 */
#ifndef LPC81X_SMW_REGS_HPP
#define LPC81X_SWM_REGS_HPP

namespace registers {
namespace swm {

enum pinAssign : uint8_t {
  PIO0_0 = 0U,   /**< assign to pin P0_0. */
  PIO0_1 = 1U,   /**< assign to pin pin P0_1. */
  PIO0_2 = 2U,   /**< assign to pin pin P0_2. */
  PIO0_3 = 3U,   /**< assign to pin pin P0_3. */
  PIO0_4 = 4U,   /**< assign to pin pin P0_4. */
  PIO0_5 = 5U,   /**< assign to pin pin P0_5. */
  PIO0_6 = 6U,   /**< assign to pin pin P0_6. */
  PIO0_7 = 7U,   /**< assign to pin pin P0_7. */
  PIO0_8 = 8U,   /**< assign to pin pin P0_8. */
  PIO0_9 = 9U,   /**< assign to pin pin P0_9. */
  PIO0_10 = 10U, /**< assign to pin pin P0_10. */
  PIO0_11 = 11U, /**< assign to pin pin P0_11. */
  PIO0_12 = 12U, /**< assign to pin pin P0_12. */
  PIO0_13 = 13U, /**< assign to pin pin P0_13. */
  PIO0_14 = 14U, /**< assign to pin pin P0_14. */
  PIO0_15 = 15U, /**< assign to pin pin P0_15. */
  PIO0_16 = 16U, /**< assign to pin pin P0_16. */
  PIO0_17 = 17U, /**< assign to pin pin P0_17. */
  RESET = 0xffU  /**< assign to nothing */
};

enum functionMovable : uint8_t {
  SWM_USART0_TXD_O = 0U,     /**< UART0 TXD Output */
  SWM_USART0_RXD_I = 1U,     /**< UART0 RXD Input */
  SWM_USART0_RTS_O = 2U,     /**< UART0 RTS Output */
  SWM_USART0_CTS_I = 3U,     /**< UART0 CTS Input */
  SWM_USART0_SCLK_IO = 4U,   /**< UART0 SCLK I/O */
  SWM_USART1_TXD_O = 5U,     /**< UART1 TXD Output */
  SWM_USART1_RXD_I = 6U,     /**< UART1 RXD Input */
  SWM_USART1_RTS_O = 7U,     /**< UART1 RTS Output */
  SWM_USART1_CTS_I = 8U,     /**< UART1 CTS Input */
  SWM_USART1_SCLK_IO = 9U,   /**< UART1 SCLK I/O */
  SWM_USART2_TXD_O = 10U,    /**< UART2 TXD Output */
  SWM_USART2_RXD_I = 11U,    /**< UART2 RXD Input */
  SWM_USART2_RTS_O = 12U,    /**< UART2 RTS Output */
  SWM_USART2_CTS_I = 13U,    /**< UART2 CTS Input */
  SWM_USART2_SCLK_IO = 14U,  /**< UART2 SCLK I/O */
  SWM_SPI0_SCK_IO = 15U,     /**< SPI0 SCK I/O */
  SWM_SPI0_MOSI_IO = 16U,    /**< SPI0 MOSI I/O */
  SWM_SPI0_MISO_IO = 17U,    /**< SPI0 MISO I/O */
  SWM_SPI0_SSEL_IO = 18U,    /**< SPI0 SSEL I/O */
  SWM_SPI1_SCK_IO = 19U,     /**< SPI1 SCK I/O */
  SWM_SPI1_MOSI_IO = 20U,    /**< SPI1 MOSI I/O */
  SWM_SPI1_MISO_IO = 21U,    /**< SPI1 MISO I/O */
  SWM_SPI1_SSEL_IO = 22U,    /**< SPI1 SSEL I/O */
  SWM_SCT0_IN_0_I = 23U,     /**< SCT Input 0*/
  SWM_SCT0_IN_1_I = 24U,     /**< SCT Input 1*/
  SWM_SCT0_IN_2_I = 25U,     /**< SCT Input 2*/
  SWM_SCT0_IN_3_I = 26U,     /**< SCT Input 3*/
  SWM_SCT0_OUT_0_O = 27U,    /**< SCT Output 0*/
  SWM_SCT0_OUT_1_O = 28U,    /**< SCT Output 1*/
  SWM_SCT0_OUT_2_O = 29U,    /**< SCT Output 2*/
  SWM_SCT0_OUT_3_O = 30U,    /**< SCT Output 3*/
  SWM_I2C0_SDA_IO = 31U,     /**< I2C SDA I/O */
  SWM_I2C0_SCL_IO = 32U,     /**< I2C SCL I/O */
  SWM_ACMP_O = 33U,          /**< ACMP Output */
  SWM_CLKOUT_O = 34U,        /**< CLKOUT Output */
  SWM_GPIO_INT_BMAT_O = 35U, /**< GPIO INT BMAT Output */
};

enum functionFixed : uint16_t {
  SWM_EN0_NONE = 0,           /**< No change for enable 0 */
  SWM_EN0_ACMP_I1 = (1 << 0), /**< ACMP I1 */
  SWM_EN0_ACMP_I2 = (1 << 1), /**< ACMP I2 */
  SWM_EN0_SWCLK = (1 << 2),   /**< SWCLK */
  SWM_EN0_SWDIO = (1 << 3),   /**< SWDIO */
  SWM_EN0_XTALIN = (1 << 4),  /**< XTALIN */
  SWM_EN0_XTALOUT = (1 << 5), /**< XTALOUT */
  SWM_EN0_RST = (1 << 6),     /**< Reset */
  SWM_EN0_CLKIN = (1 << 7),   /**< Clock Input */
  SWM_EN0_VDDCMP = (1 << 8)   /**< VDD */
};

struct registers {
  volatile uint32_t PINASSIGN[9]; /* Pin Assign register array */
  volatile uint32_t RESERVED0[103];
  volatile uint32_t PINENABLE0; /* Pin Enable register */
};
}  // namespace swm
}  // namespace registers

#endif