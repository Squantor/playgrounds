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

template <typename, std::size_t = 64> struct SqFunction;

template <class T> struct IsASimpleFunction : std::false_type {
};

template <class Sig, size_t C>
struct IsASimpleFunction<SqFunction<Sig, C>> : std::true_type {
};

template <typename Function, typename Return, typename... Arguments>
concept ValidFunctor =
    std::is_invocable_r_v<Return, std::decay_t<Function> &, Arguments...> &&
    !IsASimpleFunction<std::decay_t<Function>>::value &&
    std::copy_constructible<std::decay_t<Function>>;

template <typename Return, typename... Arguments, std::size_t capacity>
struct SqFunction<Return(Arguments...), capacity> {
   /**
    * @brief Constructor for all callable types
    * @tparam Callable
    * @param function
    */
   template <typename Callable>
   SqFunction(Callable &&function)
      requires ValidFunctor<Callable, Return, Arguments...>
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

   SqFunction(const SqFunction &other)
   {
      if (other.function_pointer) {
         function_pointer = other.cloner_function(other.function_pointer,
                                                  this->function_buffer);
         invoker_function = other.invoker_function;
         deleter_function = other.deleter_function;
         cloner_function = other.cloner_function;
         mover_function = other.mover_function;
      }
   }

   SqFunction &operator=(const SqFunction &other)
   {
      SqFunction temp(other);
      this->swap(temp);
      return *this;
   }

   SqFunction &operator=(SqFunction &&other)
   {
      SqFunction temp(std::move(other));
      this->swap(temp);
      return *this;
   }

   SqFunction(SqFunction &&other)
   {
      this->swap(other);
   }

   Return operator()(Arguments... args) const
   {
      return invoker_function(function_pointer,
                              std::forward<Arguments>(args)...);
   }

   // Note: not noexcept and not exception safe, can be implemented better.
   void swap(SqFunction &other)
   {
      if (this == &other)
         return;

      alignas(std::max_align_t) char tmp[sizeof(function_buffer)];
      void *tptr = nullptr;

      MoverFunction this_mover = mover_function;
      DeleterFunction this_deleter = deleter_function;

      // 1) move *this -> tmp
      if (this_mover && function_pointer) {
         tptr = this_mover(function_pointer, tmp);
         this_deleter(function_pointer);
         function_pointer = nullptr;
      }

      // 2) move other -> *this
      if (other.mover_function && other.function_pointer) {
         function_pointer =
             other.mover_(other.function_pointer, function_buffer);
         other.deleter_function(other.function_pointer);
         other.function_pointer = nullptr;
      }

      // 3) move tmp -> other
      if (tptr) {
         if (this_mover) {
            other.function_pointer = this_mover(tptr, other.function_buffer);
            this_deleter(tptr);
         }
      }
      std::swap(invoker_function, other.invoker_function);
      std::swap(deleter_function, other.deleter_function);
      std::swap(cloner_function, other.cloner_function);
      std::swap(mover_function, other.mover_function);
   }

   explicit operator bool() const noexcept
   {
      return invoker_function != nullptr;
   }

   void reset() noexcept
   {
      SqFunction{}.swap(*this);
   }

 private:
   void *function_pointer = nullptr;

   using InvokerFunction = Return (*)(void *, Arguments &&...);
   using DeleterFunction = void (*)(void *);
   using ClonerFunction = void *(*) (void *, char *);
   using MoverFunction = void *(*) (void *, char *);
   InvokerFunction invoker_function = nullptr;
   DeleterFunction deleter_function = nullptr;
   ClonerFunction cloner_function = nullptr;
   MoverFunction mover_function = nullptr;

   static constexpr std::size_t metadata_size =
       sizeof(decltype(function_pointer)) + sizeof(InvokerFunction) +
       sizeof(DeleterFunction) + sizeof(ClonerFunction) + sizeof(MoverFunction);
   static_assert(capacity >= metadata_size,
                 "capacity is too small for metadata");
   static constexpr size_t buffer_capacity = capacity - metadata_size;

   alignas(std::max_align_t) char function_buffer[buffer_capacity];
};

#endif