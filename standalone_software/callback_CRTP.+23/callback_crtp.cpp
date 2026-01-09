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

enum class Status { Ok = 0, Error };

/**
 * @brief CRTP base class for callbacks/Asynchronous API
 * @tparam Derived class to be derived
 */
template <typename Derived> struct AsyncBase {
   /**
    * @brief Progress whatever needs to be run
    */
   void Progress() noexcept
   {
      static_cast<Derived *>(this)->ProgressImpl();
   }
   /**
    * @brief Callback when something has completed
    */
   void Callback(Status status) noexcept
   {
      static_cast<Derived *>(this)->CallbackImpl(status);
   }
};

/**
 * @brief Type erasure for callbacks
 * Helper class to do type erasure for callbacks
 */
struct CallbackEntry {
   void *obj;
   void (*fn)(void *, Status status);
};

template <typename T>
concept HasAsyncInterface = requires(T t, Status s) {
   { t.ProgressImpl() } noexcept;
   { t.CallbackImpl(s) } noexcept;
};

/**
 * @brief
 */
struct AsyncLL : public AsyncBase<AsyncLL> {
   AsyncLL() : callback_target(nullptr), callback_fn(nullptr)
   {
   }

   template <HasAsyncInterface HalT> void SetCallbackTarget(HalT *hal)
   {
      callback_target = static_cast<void *>(hal);
      callback_fn = &CallCallback<HalT>;
   }

   void ProgressImpl() noexcept
   {
      if (callback_target) {
         callback_fn(callback_target, Status::Error);
         callback_target = nullptr;
      }
   }

   void CallbackImpl(Status) noexcept
   {  // LL driver is never called back
   }

 private:
   void *callback_target;

   using CallbackFn = void (*)(void *, Status);
   CallbackFn callback_fn;

   template <HasAsyncInterface HalT>
   static void CallCallback(void *h, Status status) noexcept
   {
      static_cast<HalT *>(h)->Callback(status);
   }
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

   template <HasAsyncInterface DriverT> void SetCallback(DriverT *drv) noexcept
   {
      callbacks[head].obj = static_cast<void *>(drv);
      callbacks[head].fn = &CallDriver<DriverT>;
      head = (head + 1) % max_callbacks;
   }

   void ProgressImpl() noexcept
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

   void CallbackImpl(Status status) noexcept
   {
      if (current.obj) {
         current.fn(current.obj, status);
         current.obj = nullptr;
         current.fn = nullptr;
      }
   }

 private:
   std::size_t head, tail;
   std::array<CallbackEntry, max_callbacks> callbacks;
   CallbackEntry current;

   template <HasAsyncInterface DriverT>
   static void CallDriver(void *d, Status status)
   {
      static_cast<DriverT *>(d)->Callback(status);
   }
};

// --- Drivers (CRTP)
struct AsyncDriver : public AsyncBase<AsyncDriver> {
   void CallbackImpl(Status status) noexcept
   {
      current_status = status;
      counter++;
   }
   void ProgressImpl() noexcept
   {
   }
   std::uint32_t counter = 0;
   Status current_status = Status::Ok;
};

// --- Wiring and test
AsyncLL dut_ll;
AsyncHal<dut_ll, 4> dut_hal;

AsyncDriver driver1;
AsyncDriver driver2;

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