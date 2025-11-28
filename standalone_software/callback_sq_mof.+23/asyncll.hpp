/*
SPDX-License-Identifier: MIT

Copyright (c) 2025 Bart Bilos
For conditions of distribution and use, see LICENSE file
*/
/**
 * \file
 *
 */

#include "sq_mof.hpp"

using AsyncCallback = MyMoveOnlyFunction<void(void), 32>;

struct AsyncLL {

   AsyncLL() : callback(nullptr)
   {
   }

   void SetCallback(AsyncCallback hal_callback)
   {
      callback = std::move(hal_callback);
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

 private:
   AsyncCallback callback;
};