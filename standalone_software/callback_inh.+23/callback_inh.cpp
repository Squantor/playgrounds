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

struct AsyncInterface {
   /**
    * @brief Progress function for asynchronous interfaces
    * Usually callbacks are called from this context to upper levels
    */
   virtual void Progress(void) = 0;
   /**
    * @brief Callback function for asynchronous interfaces
    * Usually called from lower levels
    */
   virtual void Callback(void) = 0;
};

struct AsyncLL : public AsyncInterface {

   AsyncLL() : callback_count(0), callback(nullptr)
   {
   }

   void SetCallback(AsyncInterface *hal_object)
   {
      this->callback = hal_object;
   }

   void Progress(void) override
   {
      if (callback != nullptr) {
         callback->Callback();
         callback = nullptr;
      }
   }

   void Callback(void) override
   {
      // empty, nothing calls this back
   }
   std::uint32_t callback_count;

 private:
   AsyncInterface *callback;
};

template <auto &ll_object, std::size_t max_callbacks>
struct AsyncHal : public AsyncInterface {
   AsyncHal() : current_callback(nullptr), callback_head(0), callback_tail(0)
   {
      callbacks.fill(nullptr);
   }

   void Reset(void)
   {
      callback_head = 0;
      callback_tail = 0;
      current_callback = nullptr;
      callbacks.fill(nullptr);
   }

   void SetCallback(AsyncInterface *driver_object)
   {
      callbacks[callback_head] = driver_object;
      callback_head = (callback_head + 1) % max_callbacks;
   }

   void Progress(void) override
   {
      if (current_callback == nullptr) {
         if (callback_head != callback_tail) {
            current_callback = callbacks[callback_tail];
            ll_object.SetCallback(this);
            callback_tail = (callback_tail + 1) % max_callbacks;
         }
      }
      ll_object.Progress();
   }

   void Callback(void) override
   {
      if (current_callback != nullptr) {
         current_callback->Callback();
         current_callback = nullptr;
      }
   }

 private:
   AsyncInterface *current_callback;
   std::size_t callback_head, callback_tail;
   std::array<AsyncInterface *, max_callbacks> callbacks;
};

struct AsyncDriver1 : public AsyncInterface {
   void Callback(void) override
   {
      std::printf("Driver1 callback\n");
      counter++;
   }

   void Progress(void) override
   {
      std::printf("Driver1 progress\n");
   }
   std::uint32_t counter = 0;
};

struct AsyncDriver2 : public AsyncInterface {
   void Callback(void) override
   {
      std::printf("Driver2 callback\n");
      counter++;
   }

   void Progress(void) override
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
   dut_hal.SetCallback(&driver1);
   dut_hal.SetCallback(&driver2);
   dut_hal.Progress();
   dut_hal.Progress();
   dut_hal.Progress();

   MINUNIT_CHECK(driver1.counter == 1);
   MINUNIT_CHECK(driver2.counter == 1);
}