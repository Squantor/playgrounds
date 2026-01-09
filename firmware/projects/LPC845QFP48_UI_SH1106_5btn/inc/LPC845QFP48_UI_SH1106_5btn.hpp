/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2025 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 * @brief board support code for modifications to small LPC845BD48 nuclone
 */
#ifndef NUCLONE_LPC845BD48_SMALL_NUCLONE_SH1106_I2C_HPP
#define NUCLONE_LPC845BD48_SMALL_NUCLONE_SH1106_I2C_HPP

#include <nxp/libmcu_LPC845M301BD48_hal.hpp>
#include <drivers/SH1106_i2c.hpp>

// pin types
// Crystal osillator pins
using PinXtalIn = libmcuhw::Pin<libmcuhw::IoPorts::Port0, libmcuhw::IoPins::Pin08>;
using PinXtalOut = libmcuhw::Pin<libmcuhw::IoPorts::Port0, libmcuhw::IoPins::Pin09>;
// uart pins
using PinDebugUartTx = libmcuhw::Pin<libmcuhw::IoPorts::Port0, libmcuhw::IoPins::Pin25>;
using PinDebugUartRx = libmcuhw::Pin<libmcuhw::IoPorts::Port0, libmcuhw::IoPins::Pin24>;
// bootloader entry switch pin
using PinBootloader = libmcuhw::Pin<libmcuhw::IoPorts::Port0, libmcuhw::IoPins::Pin12>;

// pin function types
using FunctionXtalIn = libmcuhw::swm::PinFunction<libmcuhw::swm::PinFunctions::XtalIn>;
using FunctionXtalOut = libmcuhw::swm::PinFunction<libmcuhw::swm::PinFunctions::XtalOut>;
using FunctionUartDebugTx = libmcuhw::swm::PinFunction<libmcuhw::swm::PinFunctions::Uart0TxOut>;
using FunctionUartDebugRx = libmcuhw::swm::PinFunction<libmcuhw::swm::PinFunctions::Uart0RxIn>;

// SDA pin with 2.2K pull up resistor
using PinI2cSda = libmcuhw::Pin<libmcuhw::IoPorts::Port0, libmcuhw::IoPins::Pin11>;
// SCL pin with 2.2K pull up resistor
using PinI2cScl = libmcuhw::Pin<libmcuhw::IoPorts::Port0, libmcuhw::IoPins::Pin10>;

using FunctionMainI2cSda = libmcuhw::swm::PinFunction<libmcuhw::swm::PinFunctions::I2c0SdaInOut>;
using FunctionMainI2cScl = libmcuhw::swm::PinFunction<libmcuhw::swm::PinFunctions::I2c0SclInOut>;

// pin instances
constexpr PinXtalIn pin_xtal_in;
constexpr PinXtalOut pin_xtal_out;
constexpr PinBootloader pin_bootload_switch;
constexpr PinDebugUartTx pin_debug_uart_tx;
constexpr PinDebugUartRx pin_debug_uart_rx;
constexpr PinI2cScl pin_i2c_scl;
constexpr PinI2cSda pin_i2c_sda;

// function instances
constexpr FunctionXtalIn function_xtal_in;
constexpr FunctionXtalOut function_xtal_out;
constexpr FunctionUartDebugTx function_debug_uart_tx;
constexpr FunctionUartDebugRx function_debug_uart_rx;
constexpr FunctionMainI2cScl function_main_i2c_scl;
constexpr FunctionMainI2cSda function_main_i2c_sda;

// clock configs
constexpr inline libmcuhw::clock::McuClockConfig<libmcuhw::clock::ClockInputSources::XTAL, 12'000'000u, 30'000'000u>
  nuclone_clock_config;
constexpr inline libmcuhw::clock::PeriClockConfig<nuclone_clock_config, libmcuhw::clock::PeriSelect::UART0,
                                                  libmcuhw::clock::PeriSource::MAIN>
  uart0_clock_config;
constexpr inline libmcuhw::clock::PeriClockConfig<nuclone_clock_config, libmcuhw::clock::PeriSelect::I2C0,
                                                  libmcuhw::clock::PeriSource::MAIN>
  i2c0_clock_config;

// peripheral externs
extern libmcull::iocon::Iocon<libmcuhw::IoconAddress> iocon_peripheral;
extern libmcull::swm::Swm<libmcuhw::SwmAddress> swm_periperhal;
extern libmcull::gpio::Gpio<libmcuhw::GpioAddress> gpio_peripheral;
extern libmcull::syscon::Syscon<libmcuhw::SysconAddress> syscon_peripheral;
extern libmcull::usart::UartInterrupt<libmcuhw::Usart0Address, char, 64> usart_peripheral_ll;
extern libmcull::i2c::I2cInterrupt<libmcuhw::I2c0Address> i2c_peripheral_ll;
extern libmcuhal::usart::Uart<usart_peripheral_ll, char> usart_peripheral;
extern libmcuhal::i2c::I2c<i2c_peripheral_ll, 40> i2c_peripheral;
extern libmcu::I2cDeviceAddress SH1106_i2c_address;
extern libMcuDriver::SH1106::Generic128x64 display_config;
extern libMcuDriver::SH1106::SH1106<i2c_peripheral, SH1106_i2c_address, display_config, libmcull::AssertBkpt> display;

constexpr inline std::uint32_t ticksPerSecond{100u};

extern volatile std::uint32_t ticks;  // amount of ticks passed sinds startup

/**
 * @brief initializes the board
 */
void BoardInit(void);

#endif