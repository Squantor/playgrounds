/*
SPDX-License-Identifier: MIT

Copyright (c) 2025 Bart Bilos
For conditions of distribution and use, see LICENSE file
*/
/**
 * \file callback_inh.cpp
 * Test program to check how inheritance based callbacks could work
 */
#include <array>
#include <cstdint>
#include <cstdio>
#include <minunit.h>

#include <array>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <type_traits>

// --- CRTP base
template <typename Derived> struct AsyncBase {
   void Progress()
   {
      static_cast<Derived *>(this)->ProgressImpl();
   }
   void Callback()
   {
      static_cast<Derived *>(this)->CallbackImpl();
   }
};

// --- Low level (LL). Does not depend on HAL type.
struct AsyncLL : public AsyncBase<AsyncLL> {
   AsyncLL() : callback_target(nullptr), callback_fn(nullptr)
   {
   }

   template <class HalT> void SetCallbackTarget(HalT *hal)
   {
      callback_target = static_cast<void *>(hal);
      callback_fn = &CallCallback<HalT>;
   }

   void ProgressImpl()
   {
      if (callback_target) {
         callback_fn(callback_target);
         callback_target = nullptr;
      }
   }

   void CallbackImpl()
   { /* not used for LL */
   }

 private:
   void *callback_target;

   using CallbackFn = void (*)(void *);
   CallbackFn callback_fn;

   template <class HalT> static void CallCallback(void *h)
   {
      static_cast<HalT *>(h)->Callback();
   }
};

// --- Drivers (CRTP)
struct AsyncDriver1 : public AsyncBase<AsyncDriver1> {
   void CallbackImpl()
   {
      std::printf("Driver1 callback\n");
      counter++;
   }
   void ProgressImpl()
   {
      std::printf("Driver1 progress\n");
   }
   std::uint32_t counter = 0;
};

struct AsyncDriver2 : public AsyncBase<AsyncDriver2> {
   void CallbackImpl()
   {
      std::printf("Driver2 callback\n");
      counter++;
   }
   void ProgressImpl()
   {
      std::printf("Driver2 progress\n");
   }
   std::uint32_t counter = 0;
};

// --- HAL using pointer type-erasure for heterogeneous drivers
template <AsyncLL &ll_object, std::size_t max_callbacks>
struct AsyncHal : public AsyncBase<AsyncHal<ll_object, max_callbacks>> {

   AsyncHal() : head(0), tail(0), callbacks(), current{nullptr, nullptr}
   {
      for (auto &e : callbacks) {
         e.obj = nullptr;
         e.fn = nullptr;
      }
   }

   template <class DriverT> void SetCallback(DriverT *drv)
   {
      callbacks[head].obj = static_cast<void *>(drv);
      callbacks[head].fn = &CallDriver<DriverT>;
      head = (head + 1) % max_callbacks;
   }

   void ProgressImpl()
   {
      if (current.obj == nullptr) {
         if (head != tail) {
            current = callbacks[tail];
            ll_object.SetCallbackTarget(this);
            callbacks[tail].obj = nullptr;  // optional: clear slot
            callbacks[tail].fn = nullptr;
            tail = (tail + 1) % max_callbacks;
         }
      }
      ll_object.Progress();
   }

   void CallbackImpl()
   {
      if (current.obj) {
         current.fn(current.obj);
         current.obj = nullptr;
         current.fn = nullptr;
      }
   }

 private:
   struct Entry {
      void *obj;
      void (*fn)(void *);
   };

   std::size_t head, tail;
   std::array<Entry, max_callbacks> callbacks;
   Entry current;

   template <class DriverT> static void CallDriver(void *d)
   {
      static_cast<DriverT *>(d)->Callback();
   }
};

// --- Wiring and test
AsyncLL dut_ll;
AsyncHal<dut_ll, 4> dut_hal;

AsyncDriver1 driver1;
AsyncDriver2 driver2;

MINUNIT_ADD(callback_test, nullptr, nullptr)
{
   dut_hal.SetCallback(&driver1);
   dut_hal.SetCallback(&driver2);
   dut_hal.Progress();
   dut_hal.Progress();
   dut_hal.Progress();

   MINUNIT_CHECK(driver1.counter == 1);
   MINUNIT_CHECK(driver2.counter == 1);
}