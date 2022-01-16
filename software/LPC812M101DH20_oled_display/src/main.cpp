/*
SPDX-License-Identifier: MIT

Copyright (c) 2021 Bart Bilos
For conditions of distribution and use, see LICENSE file
*/
#include <board.hpp>
#include <SSD1306.hpp>

uint32_t ticks;

using namespace SSD1306;

extern "C" {
void SysTick_Handler(void) {
  ticks++;
  GpioSetPortToggle(GPIO, PORT_LED, 1 << PIN_LED);
}
}

uint32_t startI2CTransfer(I2C_Type *peripheral, uint8_t address) {
  uint32_t busStatus;
  i2cSetMasterData(peripheral, address);
  i2cSetMasterControl(peripheral, I2C_MSCTL_MSTSTART);
  do {
    busStatus = i2cGetStatus(peripheral);
  } while (((busStatus & (I2C_STAT_MSTPENDING | I2C_STAT_EVENTTIMEOUT | I2C_STAT_SCLTIMEOUT)) == 0));
  return busStatus;
}

uint8_t sendI2CData(I2C_Type *peripheral, uint8_t data) {
  uint32_t busStatus;
  i2cSetMasterData(peripheral, data);
  i2cSetMasterControl(peripheral, I2C_MSCTL_MSTCONTINUE);
  do {
    busStatus = i2cGetStatus(peripheral);
  } while (((busStatus & (I2C_STAT_MSTPENDING | I2C_STAT_EVENTTIMEOUT | I2C_STAT_SCLTIMEOUT)) == 0));
  return busStatus;
}

void stopI2CTransfer(I2C_Type *peripheral) {
  i2cSetMasterControl(peripheral, I2C_MSCTL_MSTSTOP);
}

uint8_t transferI2CData(uint8_t *data, uint8_t length) {
  uint8_t dataIndex = 0;
  uint32_t busStatus;
  busStatus = startI2CTransfer(I2C0, data[dataIndex]);
  if ((I2C_STAT_MSTSTATE(busStatus) != I2C_STAT_MSSTATE_TRANSMIT_READY)) goto i2cStop;
  dataIndex++;
  do {
    busStatus = sendI2CData(I2C0, data[dataIndex]);
    if ((I2C_STAT_MSTSTATE(busStatus) != I2C_STAT_MSSTATE_TRANSMIT_READY)) goto i2cStop;
    dataIndex++;
  } while (dataIndex < length);
i2cStop:
  stopI2CTransfer(I2C0);
  return busStatus;
}

uint8_t SSD1306CommandList(uint8_t address, uint8_t *data, uint8_t length) {
  uint8_t dataIndex = 0;
  uint32_t busStatus;
  busStatus = startI2CTransfer(I2C0, address);
  if ((I2C_STAT_MSTSTATE(busStatus) != I2C_STAT_MSSTATE_TRANSMIT_READY)) goto i2cStop;
  do {
    busStatus = sendI2CData(I2C0, 0x00);  // Command setup
    if ((I2C_STAT_MSTSTATE(busStatus) != I2C_STAT_MSSTATE_TRANSMIT_READY)) goto i2cStop;
    busStatus = sendI2CData(I2C0, data[dataIndex]);
    if ((I2C_STAT_MSTSTATE(busStatus) != I2C_STAT_MSSTATE_TRANSMIT_READY)) goto i2cStop;
    dataIndex++;
  } while (dataIndex < length);
i2cStop:
  stopI2CTransfer(I2C0);
  return busStatus;
}

uint8_t SSD1306Command(uint8_t address, uint8_t command) {
  uint32_t busStatus;
  busStatus = startI2CTransfer(I2C0, address);
  if ((I2C_STAT_MSTSTATE(busStatus) != I2C_STAT_MSSTATE_TRANSMIT_READY)) goto i2cStop;
  busStatus = sendI2CData(I2C0, 0x00);  // Command setup
  if ((I2C_STAT_MSTSTATE(busStatus) != I2C_STAT_MSSTATE_TRANSMIT_READY)) goto i2cStop;
  busStatus = sendI2CData(I2C0, command);
  if ((I2C_STAT_MSTSTATE(busStatus) != I2C_STAT_MSSTATE_TRANSMIT_READY)) goto i2cStop;
i2cStop:
  stopI2CTransfer(I2C0);
  return busStatus;
}

int main() {
  ticks = 0;
  uint32_t currentTicks = 0;
  boardInit();
  uint8_t init1[] = {
    commands::displaySleep,
    commands::setDisplayClockDivide,
    commands::displayClockDivisor(0x80),
    commands::setMultiplexRatio,
  };
  SSD1306CommandList(0x78, init1, sizeof(init1));
  SSD1306Command(0x78, commands::multiplexRatio(31));
  uint8_t init2[] = {commands::setDisplayOffset, commands::displayOffset(0), commands::setDisplayStartLine(0),
                     commands::setChargePump};
  SSD1306CommandList(0x78, init2, sizeof(init2));
  SSD1306Command(0x78, commands::chargePumpOn(true));
  uint8_t init3[] = {commands::setMemoryAddressingMode, commands::AddressingMode(commands::horizontalMode),
                     commands::setSegmentRemap(commands::column0), commands::comOutputScanDirection(commands::remappedDirection)};
  SSD1306CommandList(0x78, init3, sizeof(init3));
  SSD1306Command(0x78, commands::setComPinsHardware);
  SSD1306Command(0x78, commands::ComPinsHardware(true, false));
  SSD1306Command(0x78, commands::setContrast);
  SSD1306Command(0x78, commands::ConstrastLevel(0x1f));
  SSD1306Command(0x78, commands::setPrechargeLevel);
  SSD1306Command(0x78, commands::prechargeLevel(0xF1));
  uint8_t init5[] = {commands::setVcomDeselectLevel,
                     commands::vcomDeselectLevel(4),
                     commands::displayOn,
                     commands::displayNormal,
                     commands::scrollOff,
                     commands::displayActive};
  SSD1306CommandList(0x78, init5, sizeof(init5));

  while (1) {
    if (currentTicks != ticks) {
      currentTicks = ticks;
      uint8_t invertDisplay;
      if (currentTicks & 8)
        invertDisplay = commands::displayInvert;
      else
        invertDisplay = commands::displayNormal;
      SSD1306CommandList(0x78, &invertDisplay, sizeof(invertDisplay));
    }
  }
}
