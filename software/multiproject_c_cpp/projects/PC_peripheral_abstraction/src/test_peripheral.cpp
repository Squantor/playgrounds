/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2021 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */

#include <array>
#include <cstdio>
#include <cstdint>
#include <MinUnit.h>

template <size_t N>
struct peripheral {
  volatile uint32_t data;
};

template <auto &P>
class peripheralGeneric {
 public:
  uint32_t transceive(uint16_t buf, uint32_t bits) {
    P.data = buf;
    P.data = P.data + bits;
    return P.data;
  }

 private:
};

template <auto &P>
class deviceGeneric {
 public:
  uint32_t doSomething(uint16_t value) {
    return P.transceive(value, 8);
  }

 private:
};

peripheral<10> hardware0;
peripheralGeneric<hardware0> peripheral0;
deviceGeneric<peripheral0> device0;

MINUNIT_ADD(testAtomicUint16, NULL, NULL) {
  uint32_t value = device0.doSomething(10);
  minUnitCheck(18u == value);
}