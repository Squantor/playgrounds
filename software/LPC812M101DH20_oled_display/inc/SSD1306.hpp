/*
SPDX-License-Identifier: MIT

Copyright (c) 2022 Bart Bilos
For conditions of distribution and use, see LICENSE file
*/
#ifndef SSD1306_HPP
#define SSD1306_HPP

#include <stdint.h>

namespace SSD1306 {
namespace commands {
constexpr uint8_t setVcomDeselectLevel = 0xDB;
consteval uint8_t vcomDeselectLevel(uint8_t level) {
  return (level & 0x07) << 4;
}
constexpr uint8_t setComPinsHardware = 0xDA;
consteval uint8_t ComPinsHardware(bool sequential, bool remapped) {
  uint8_t configuration = 0x02;
  if (sequential != true) configuration |= 0x10;
  if (remapped) configuration |= 0x20;
  return configuration;
}

constexpr uint8_t setDisplayClockDivide = 0xD5;
consteval uint8_t displayClockDivisor(uint8_t ratio) {
  return ratio;
}

constexpr uint8_t setPrechargeLevel = 0xD9;
consteval uint8_t prechargeLevel(uint8_t level) {
  return level;
}

constexpr uint8_t setDisplayOffset = 0xD3;
consteval uint8_t displayOffset(uint8_t offset) {
  return offset;
}

enum scanDirection : uint8_t {
  normalDirection = 0x00,
  remappedDirection = 0x08,
};

consteval uint8_t comOutputScanDirection(scanDirection mode) {
  return mode | 0xC0;
}

consteval uint8_t setPageStart(uint8_t address) {
  return (address & 0x07) | 0xB0;
}
constexpr uint8_t displayActive = 0xAF;     /*!< turn display on */
constexpr uint8_t displaySleep = 0xAE;      /*!< turn display off */
constexpr uint8_t setMultiplexRatio = 0xA8; /*!< multiplex ratio */
consteval uint8_t multiplexRatio(uint8_t ratio) {
  return ratio;
}
constexpr uint8_t displayInvert = 0xA7; /*!< invert display */
constexpr uint8_t displayNormal = 0xA6; /*!< normal display */
constexpr uint8_t displayRam = 0xA5;    /*!< display RAM content */
constexpr uint8_t displayOn = 0xA4;     /*!< turn all pixels on */

enum segmentMapping : uint8_t {
  column0 = 0,  /*!< Segment 0 mapped to column address 0 */
  column127 = 1 /*!< Segment 0 mapped to column address 127 */
};
/*!< @brief set segment remapping */
consteval uint8_t setSegmentRemap(segmentMapping mapping) {
  return mapping | 0xA0;
}
constexpr uint8_t setChargePump = 0x8D; /*!< set charge pump state */
consteval uint8_t chargePumpOn(bool pumpOn) {
  if (pumpOn)
    return 0x14;
  else
    return 0x10;
}
constexpr uint8_t setContrast = 0x81; /*!< set contrast level */
consteval uint8_t ConstrastLevel(uint8_t level) {
  return level;
}
consteval uint8_t setDisplayStartLine(uint8_t address) {
  return (address & 0x3F) | 0x40;
}
constexpr uint8_t scrollOn = 0x2F;
constexpr uint8_t scrollOff = 0x2E;
constexpr uint8_t setPageAddress = 0x22;
constexpr uint8_t setColumnAddress = 0x21;
constexpr uint8_t setMemoryAddressingMode = 0x20;

enum addressingModes : uint8_t {
  horizontalMode = 0, /*!< Horizontal addressing mode */
  verticalMode = 1,   /*!< vertical addressing mode */
  pageMode = 2,       /*!< page addressing mode */
  invalidMode = 3,    /*!< INVALID! DO NOT USE! */
};

consteval uint8_t AddressingMode(addressingModes mode) {
  return mode;
}

consteval uint8_t higherColumnAddress(uint8_t address) {
  return (address & 0x0F) | 0x10;
}

consteval uint8_t lowerColumnAddress(uint8_t address) {
  return (address & 0x0F) | 0x00;
}

}  // namespace commands
}  // namespace SSD1306

#endif