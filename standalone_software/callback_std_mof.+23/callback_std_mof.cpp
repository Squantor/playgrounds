/*
SPDX-License-Identifier: MIT

Copyright (c) 2025 Bart Bilos
For conditions of distribution and use, see LICENSE file
*/
/**
 * \file callback_std_mof.cpp
 * Test program to check how std::move_only_function callbacks could work
 */
#include <array>
#include <cstdint>
#include <cstdio>
#include <functional>
#include <minunit.h>

using AsyncCallback = std::move_only_function<void(void)>;

struct AsyncLL {

   AsyncLL() : callback_count(0), callback(nullptr)
   {
   }

   void SetCallback(AsyncCallback hal_callback)
   {
      this->callback = std::move(hal_callback);
   }

   void Progress(void)
   {
      if (callback != nullptr) {
         callback();
         callback = nullptr;
      }
   }

   void Callback(void)
   {
      // empty, nothing calls this back
   }
   std::uint32_t callback_count;

 private:
   AsyncCallback callback;
};

template <auto &ll_object, std::size_t max_callbacks> struct AsyncHal {
   AsyncHal() : current_callback(nullptr), callback_head(0), callback_tail(0)
   {
   }

   void Reset(void)
   {
      callback_head = 0;
      callback_tail = 0;
      current_callback = nullptr;
      for (auto &c : callbacks)
         c = AsyncCallback{};
   }

   void SetCallback(AsyncCallback driver_object)
   {
      callbacks[callback_head] = std::move(driver_object);
      callback_head = (callback_head + 1) % max_callbacks;
   }

   void Progress(void)
   {
      if (current_callback == nullptr) {
         if (callback_head != callback_tail) {
            current_callback = std::move(callbacks[callback_tail]);
            ll_object.SetCallback([this]() { this->Callback(); });
            callback_tail = (callback_tail + 1) % max_callbacks;
         }
      }
      ll_object.Progress();
   }

   void Callback(void)
   {
      if (current_callback != nullptr) {
         current_callback();
         current_callback = nullptr;
      }
   }

 private:
   AsyncCallback current_callback;
   std::size_t callback_head, callback_tail;
   std::array<AsyncCallback, max_callbacks> callbacks;
};

struct AsyncDriver1 {
   void Callback(void)
   {
      std::printf("Driver1 callback\n");
      counter++;
   }

   void Progress(void)
   {
      std::printf("Driver1 progress\n");
   }
   std::uint32_t counter = 0;
};

struct AsyncDriver2 {
   void Callback(void)
   {
      std::printf("Driver2 callback\n");
      counter++;
   }

   void Progress(void)
   {
      std::printf("Driver2 progress\n");
   }
   std::uint32_t counter = 0;
};

AsyncLL dut_ll;
AsyncHal<dut_ll, 4> dut_hal;
AsyncDriver1 driver1;
AsyncDriver2 driver2;

MINUNIT_ADD(callback_test, nullptr, nullptr)
{
   dut_hal.SetCallback([]() { driver1.Callback(); });
   dut_hal.SetCallback([]() { driver2.Callback(); });
   dut_hal.Progress();
   dut_hal.Progress();
   dut_hal.Progress();

   MINUNIT_CHECK(driver1.counter == 1);
   MINUNIT_CHECK(driver2.counter == 1);
}