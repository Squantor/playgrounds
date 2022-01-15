/*
SPDX-License-Identifier: MIT

Copyright (c) 2021 Bart Bilos
For conditions of distribution and use, see LICENSE file
*/
#include <board.hpp>

uint32_t ticks;

extern "C" {
void SysTick_Handler(void) {
  ticks++;
  GpioSetPortToggle(GPIO, PORT_LED, 1 << PIN_LED);
}
}

uint8_t transferI2CData(uint8_t *data, uint8_t length) {
  uint8_t dataIndex = 0;
  uint32_t busStatus;
  i2cSetConfiguration(I2C0, I2C_CFG_MSTEN | I2C_CFG_TIMEOUTEN);
  i2cSetMasterData(I2C0, data[dataIndex]);
  i2cSetMasterControl(I2C0, I2C_MSCTL_MSTSTART);
  do {
    busStatus = i2cGetStatus(I2C0);
  } while (((busStatus & (I2C_STAT_MSTPENDING)) == 0));
  if ((I2C_STAT_MSTSTATE(busStatus) != I2C_STAT_MSSTATE_TRANSMIT_READY)) goto i2cStop;
  do {
    i2cSetMasterData(I2C0, data[dataIndex]);
    i2cSetMasterControl(I2C0, I2C_MSCTL_MSTCONTINUE);
    do {
      busStatus = i2cGetStatus(I2C0);
    } while (((busStatus & I2C_STAT_MSTPENDING) != 0));
    dataIndex++;
  } while (dataIndex < length && (I2C_STAT_MSTSTATE(busStatus) == I2C_STAT_MSSTATE_TRANSMIT_READY));
i2cStop:
  i2cSetMasterControl(I2C0, I2C_MSCTL_MSTSTOP);
  return busStatus;
}

int main() {
  ticks = 0;
  uint32_t currentTicks = 0;
  boardInit();
  while (1) {
    if (currentTicks != ticks) {
      uint8_t testDisplay[] = {0x3C};
      transferI2CData(testDisplay, sizeof(testDisplay));
    }
  }
}
