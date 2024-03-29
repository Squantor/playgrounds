/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2021 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
#include <nuclone_LPC845M301BD48_sharp_lcd.hpp>
#include <span>
#include <array>

instances::spi::spi<peripherals::SPI0_cpp, instances::spi::spiChipEnables> spi0Peripheral;

void crudeDelay(uint32_t iterations) {
  for (uint32_t i = iterations; i > 0; i--) {
    __NOP();
    __NOP();
    __NOP();
    __NOP();
    __NOP();
    __NOP();
    __NOP();
    __NOP();
  }
}

void boardInit(void) {
  sysconEnableClocks(SYSCON, CLKCTRL0_IOCON | CLKCTRL0_GPIO0 | CLKCTRL0_SWM | CLKCTRL0_SPI0, CLKCTRL1_NONE);
  ioconSetupPin(IOCON, IOCON_DISP_CE, IOCON_MODE_INACTIVE);
  ioconSetupPin(IOCON, IOCON_DISP_MOSI, IOCON_MODE_INACTIVE);
  ioconSetupPin(IOCON, IOCON_DISP_SCK, IOCON_MODE_INACTIVE);
  ioconSetupPin(IOCON, IOCON_LED, IOCON_MODE_INACTIVE);
  // setup crystal oscillator and PLL to run core at 30MHz
  ioconSetupPin(IOCON, IOCON_XTAL_IN, IOCON_MODE_INACTIVE);
  ioconSetupPin(IOCON, IOCON_XTAL_OUT, IOCON_MODE_INACTIVE);
  swmEnableFixedPin(SWM, SWM_EN0_XTALIN | SWM_EN0_XTALOUT, SWM_EN1_NONE);
  sysconSysOscControl(SYSCON, SYSOSCCTRL_FREQ_1_20MHZ);
  sysconPowerEnable(SYSCON, PDRUNCFG_SYSOSC);
  crudeDelay(6000);
  sysconExternalClockSelect(SYSCON, EXTCLKSEL_SYSOSC);
  sysconSysPllClockSelect(SYSCON, SYSPLLCLKSEL_EXTCLK);
  FlashControlFlashClocks(FLASHTIM_2_CLOCKS);
  sysconPowerDisable(SYSCON, PDRUNCFG_SYSPLL);
  // setup PLL for 60MHz output
  sysconPllControl(SYSCON, 4, SYSPLLCTRL_POSTDIV_4);
  sysconPowerEnable(SYSCON, PDRUNCFG_SYSPLL);
  while (sysconPllStatus(SYSCON) == 0)
    ;
  // divide 60MHz from Pll to 30MHz for the CPU
  sysconMainClockDivider(SYSCON, 2);
  sysconMainClockPllSelect(SYSCON, MAINCLKPLLSEL_SYSPLL);

  // setup GPIO pin
  gpioSetPinDIROutput(GPIO, PORT_LED, PIN_LED);
  gpioPinWrite(GPIO, PORT_LED, PIN_LED, 0);

  // setup systick
  SysTick_Config(CLOCK_AHB / TICKS_PER_S);

  // setup SPI
  SwmMovablePinAssign(SWM, SWM_SPI0_SSEL0, SWM_DISP_CE);
  SwmMovablePinAssign(SWM, SWM_SPI0_MOSI, SWM_DISP_MOSI);
  SwmMovablePinAssign(SWM, SWM_SPI0_SCK, SWM_DISP_SCK);
  sysconPeripheralClockSelect(SYSCON, SPI0CLKSEL, CLKSRC_MAIN);
  spiSetDivider(SPI0, 30);
  spiSetConfig(SPI0, SPI_CFG_ENABLE | SPI_CFG_MASTER | SPI_CFG_LSBF | SPI_CFG_SPOL0);

  // disable all unneeded clocks
  sysconDisableClocks(SYSCON, CLKCTRL0_SWM, CLKCTRL1_NONE);

  // setup and clear LCD display
  spiSetTxCtrlData(SPI0,
                   SPI_TXDATCTL_TXDAT(0x4) | SPI_TXDATCTL_TXSSEL0 | SPI_TXDATCTL_EOF | SPI_TXDATCTL_RXIGNORE | SPI_TXDATCTL_LEN(3));
  while (!(spiSetGetStatus(SPI0, 0x0) & SPI_STAT_TXRDY))
    ;
  spiSetTxCtrlData(SPI0, SPI_TXDATCTL_TXDAT(0x0000) | SPI_TXDATCTL_TXSSEL0 | SPI_TXDATCTL_EOF | SPI_TXDATCTL_EOT |
                           SPI_TXDATCTL_RXIGNORE | SPI_TXDATCTL_LEN(16));
}

/*
static void waitSpiTxComplete(void) {
  while (!(spiSetGetStatus(SPI0, 0x0) & SPI_STAT_TXRDY))
    ;
}

void lcdTransfer(uint16_t *begin, uint16_t *end) {
  // transfer of 1
  if (begin + 1 == end) {
    waitSpiTxComplete();
    spiSetTxCtrlData(SPI0, SPI_TXDATCTL_TXDAT(*begin) | SPI_TXDATCTL_TXSSEL0 | SPI_TXDATCTL_EOF | SPI_TXDATCTL_EOT |
                             SPI_TXDATCTL_RXIGNORE | SPI_TXDATCTL_LEN(16));
    return;
  }
  // transfer of N
  else {
    uint16_t *p = begin;
    while (p < end) {
      waitSpiTxComplete();
      spiSetTxCtrlData(
        SPI0, SPI_TXDATCTL_TXDAT(*p) | SPI_TXDATCTL_TXSSEL0 | SPI_TXDATCTL_EOF | SPI_TXDATCTL_RXIGNORE | SPI_TXDATCTL_LEN(16));
      p++;
    }
    // line or multiline transfers need to be terminated
    waitSpiTxComplete();
    spiSetTxCtrlData(SPI0, SPI_TXDATCTL_TXDAT(0x0000) | SPI_TXDATCTL_TXSSEL0 | SPI_TXDATCTL_EOF | SPI_TXDATCTL_EOT |
                             SPI_TXDATCTL_RXIGNORE | SPI_TXDATCTL_LEN(16));
  }
}
*/

void lcdTransfer(uint16_t *begin, uint16_t *end) {
  spi0Peripheral.transmit(instances::spi::spiChipEnables::SSEL0, std::span{begin, end}, (end - begin) * 16, false);
  std::array<uint16_t, 1> endTransmit;
  spi0Peripheral.transmit(instances::spi::spiChipEnables::SSEL0, endTransmit, 16, true);
}