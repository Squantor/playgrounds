/*
SPDX-License-Identifier: MIT

Copyright (c) 2025 Bart Bilos
For conditions of distribution and use, see LICENSE file
*/
/**
 * \file sq_function.hpp
 * Simple std::function replacement that does not allocate
 * and is only movable. Inspiration drawn from the following tutorials:
 * https://medium.com/@sgn00/diving-into-std-function-d342e4b58ea7
 * https://blog.rink.nu/2024/02/24/implementing-a-stdfunction-like-wrapper-in-c-part-1-type-erasing/
 */
#ifndef SQ_FUNCTION_HPP
#define SQ_FUNCTION_HPP

#include <memory>
#include <stdexcept>
#include <utility>

template <typename, std::size_t = 32> struct SqFunction;

template <typename Return, typename... Arguments, std::size_t capacity>
struct SqFunction<Return(Arguments...), capacity> {
   /**
    * @brief Constructor for all callable types
    * @tparam Callable
    * @param function
    */
   template <typename Callable> SqFunction(Callable &&function)
   {
      using DecayedCallable = std::decay_t<Callable>;
      // Check that our buffer can fit F at compile time
      static_assert(sizeof(DecayedCallable) <= buffer_capacity,
                    "Callable too large for in-place buffer");
      static_assert(alignof(DecayedCallable) <= alignof(std::max_align_t),
                    "Alignment mismatch");
      // placement new into our buffer
      function_pointer = new (function_buffer)
          DecayedCallable(std::forward<Callable>(function));

      // Set up invoker function
      invoker_function = [](void *ptr, Arguments &&...args) -> Return {
         return (*static_cast<DecayedCallable *>(ptr))(
             std::forward<Arguments>(args)...);
      };

      // Set up deleter function
      deleter_function = [](void *ptr) {
         static_cast<DecayedCallable *>(ptr)->~DecayedCallable();
      };
   }
   /**
    * @brief Destroy Function object
    */
   ~SqFunction()
   {
      if (function_pointer && deleter_function) {
         deleter_function(function_pointer);
      }
   }

   // TODO: Implement copy and move operations

   Return operator()(Arguments... args) const
   {
      return invoker_function(function_pointer,
                              std::forward<Arguments>(args)...);
   }

 private:
   void *function_pointer = nullptr;

   using InvokerFunction = Return (*)(void *, Arguments &&...);
   using DeleterFunction = void (*)(void *);
   InvokerFunction invoker_function = nullptr;
   DeleterFunction deleter_function = nullptr;

   static constexpr size_t buffer_capacity =
       capacity - sizeof(function_pointer) - sizeof(invoker_function) -
       sizeof(deleter_function);
   // fixed-size inplace buffer
   alignas(std::max_align_t) char function_buffer[buffer_capacity];
};

#endif