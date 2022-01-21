/*
SPDX-License-Identifier: MIT

Copyright (c) 2021 Bart Bilos
For conditions of distribution and use, see LICENSE file
*/
#include <board.hpp>
#include <SSD1306.hpp>
#include <font_8x8.h>

using namespace util;

const uint8_t init128x64[] = {SSD1306::displaySleep,
                              SSD1306::setDisplayClockDivide,
                              SSD1306::displayClockDivisor(0x80),
                              SSD1306::setMultiplexRatio,
                              SSD1306::multiplexRatio(63),
                              SSD1306::setDisplayOffset,
                              SSD1306::displayOffset(0),
                              SSD1306::setDisplayStartLine(0),
                              SSD1306::setChargePump,
                              SSD1306::chargePumpOn(true),
                              SSD1306::setMemoryAddressingMode,
                              SSD1306::AddressingMode(SSD1306::horizontalMode),
                              SSD1306::setSegmentRemap(SSD1306::column127),
                              SSD1306::comOutputScanDirection(SSD1306::remappedDirection),
                              SSD1306::setComPinsHardware,
                              SSD1306::ComPinsHardware(SSD1306::alternatingNormal),
                              SSD1306::setContrast,
                              SSD1306::ConstrastLevel(0x01),
                              SSD1306::setPrechargeLevel,
                              SSD1306::prechargeLevel(0xF1),
                              SSD1306::setVcomDeselectLevel,
                              SSD1306::vcomDeselectLevel(4),
                              SSD1306::displayOn,
                              SSD1306::displayNormal,
                              SSD1306::scrollOff,
                              SSD1306::displayActive};
const uint8_t init128x32[] = {SSD1306::displaySleep,
                              SSD1306::setDisplayClockDivide,
                              SSD1306::displayClockDivisor(0x80),
                              SSD1306::setMultiplexRatio,
                              SSD1306::multiplexRatio(31),
                              SSD1306::setDisplayOffset,
                              SSD1306::displayOffset(0),
                              SSD1306::setDisplayStartLine(0),
                              SSD1306::setChargePump,
                              SSD1306::chargePumpOn(true),
                              SSD1306::setMemoryAddressingMode,
                              SSD1306::AddressingMode(SSD1306::horizontalMode),
                              SSD1306::setSegmentRemap(SSD1306::column127),
                              SSD1306::comOutputScanDirection(SSD1306::remappedDirection),
                              SSD1306::setComPinsHardware,
                              SSD1306::ComPinsHardware(SSD1306::sequentialNormal),
                              SSD1306::setContrast,
                              SSD1306::ConstrastLevel(0x01),
                              SSD1306::setPrechargeLevel,
                              SSD1306::prechargeLevel(0xF1),
                              SSD1306::setVcomDeselectLevel,
                              SSD1306::vcomDeselectLevel(4),
                              SSD1306::displayOn,
                              SSD1306::displayNormal,
                              SSD1306::scrollOff,
                              SSD1306::displayActive};

uint32_t ticks;

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

uint8_t transferI2CData(I2C_Type *peripheral, const uint8_t *data, uint16_t length) {
  uint16_t dataIndex = 0;
  uint32_t busStatus;
  do {
    busStatus = sendI2CData(peripheral, data[dataIndex]);
    if ((I2C_STAT_MSTSTATE(busStatus) != I2C_STAT_MSSTATE_TRANSMIT_READY)) goto i2cStop;
    dataIndex++;
  } while (dataIndex < length);
i2cStop:
  stopI2CTransfer(peripheral);
  return busStatus;
}

uint8_t SSD1306CommandList(uint8_t address, const uint8_t *data, uint8_t length) {
  uint8_t dataIndex = 0;
  uint32_t busStatus;
  busStatus = startI2CTransfer(I2C0, address);
  if ((I2C_STAT_MSTSTATE(busStatus) != I2C_STAT_MSSTATE_TRANSMIT_READY)) goto i2cStop;
  busStatus = sendI2CData(I2C0, 0x00);  // Command setup
  if ((I2C_STAT_MSTSTATE(busStatus) != I2C_STAT_MSSTATE_TRANSMIT_READY)) goto i2cStop;
  do {
    busStatus = sendI2CData(I2C0, data[dataIndex]);
    if ((I2C_STAT_MSTSTATE(busStatus) != I2C_STAT_MSSTATE_TRANSMIT_READY)) goto i2cStop;
    dataIndex++;
  } while (dataIndex < length);
i2cStop:
  stopI2CTransfer(I2C0);
  return busStatus;
}

uint8_t SSD1306DataList(uint8_t address, const uint8_t *data, uint8_t length) {
  uint8_t dataIndex = 0;
  uint32_t busStatus;
  busStatus = startI2CTransfer(I2C0, address);
  if ((I2C_STAT_MSTSTATE(busStatus) != I2C_STAT_MSSTATE_TRANSMIT_READY)) goto i2cStop;
  busStatus = sendI2CData(I2C0, 0x40);  // data write
  if ((I2C_STAT_MSTSTATE(busStatus) != I2C_STAT_MSSTATE_TRANSMIT_READY)) goto i2cStop;
  do {
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

  SSD1306CommandList(0x78, init128x64, sizeof(init128x64));
  uint8_t display[] = {SSD1306::setPageAddress, 0, 0x07, SSD1306::setColumnAddress, 0, 127};
  SSD1306CommandList(0x78, display, sizeof(display));
  startI2CTransfer(I2C0, 0x78);
  sendI2CData(I2C0, 0x40);
  transferI2CData(I2C0, font8x8VerticalFlipped, 760);
  startI2CTransfer(I2C0, 0x78);
  sendI2CData(I2C0, 0x40);
  transferI2CData(I2C0, font8x8VerticalFlipped, 264);

  while (1) {
    if (currentTicks != ticks) {
      currentTicks = ticks;
      uint8_t invertDisplay;
      if (currentTicks & 2)
        invertDisplay = SSD1306::displayInvert;
      else
        invertDisplay = SSD1306::displayNormal;
      SSD1306CommandList(0x78, &invertDisplay, sizeof(invertDisplay));
    }
  }
}
