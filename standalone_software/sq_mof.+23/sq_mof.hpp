/*
SPDX-License-Identifier: MIT

Copyright (c) 2025 Bart Bilos
For conditions of distribution and use, see LICENSE file
*/
/**
 * \file sq_mof.hpp
 * Reimplementation of a simple in place std::move_only_function
 */
#ifndef SQ_MOF_HPP
#define SQ_MOF_HPP

#include <cstring>
#include <memory>
#include <utility>

struct MyMoveOnlyFunctionSomeClass {
};

union MyMoveOnlyFunctionUnion {
   void *some_ptr;
   void (*some_func)();
   void (MyMoveOnlyFunctionSomeClass::*some_member_func)();
};

template <typename T, std::size_t size> struct MyMoveOnlyFunctionStorage {
   static constexpr auto capacity()
   {
      return size;
   }

   union {
      MyMoveOnlyFunctionUnion mfu;
      std::byte buffer[capacity()];
   };

   auto ptr()
   {
      return reinterpret_cast<T *>(&buffer);
   }

   MyMoveOnlyFunctionStorage() = default;
   MyMoveOnlyFunctionStorage(const MyMoveOnlyFunctionStorage &) = delete;
   MyMoveOnlyFunctionStorage &
   operator=(const MyMoveOnlyFunctionStorage &) = delete;
};

template <typename ReturnType, typename... Args>
struct MyMoveOnlyFunctionInterface {
   virtual ~MyMoveOnlyFunctionInterface() = default;
   virtual ReturnType operator()(Args...) = 0;
};

template <typename Fn, typename ReturnType, typename... Args>
class MyMoveOnlyFunctionImpl
    : public MyMoveOnlyFunctionInterface<ReturnType, Args...>
{
   Fn fn;

 public:
   MyMoveOnlyFunctionImpl(Fn fn) : fn(std::move(fn))
   {
   }

   ReturnType operator()(Args... args) override
   {
      return fn(std::forward<Args>(args)...);
   }
};

template <typename, size_t = 32> class MyMoveOnlyFunction;

template <typename ReturnType, typename... Args, std::size_t size>
struct MyMoveOnlyFunction<ReturnType(Args...), size> {

   MyMoveOnlyFunction() noexcept : is_invokable{false}
   {
   }

   MyMoveOnlyFunction(std::nullptr_t) noexcept : is_invokable{false}
   {
   }

   MyMoveOnlyFunction(MyMoveOnlyFunction &&move_only_function) noexcept
       : is_invokable{std::exchange(move_only_function.is_invokable, false)}
   {
      std::memcpy(fn.buffer, move_only_function.fn.buffer, fn.capacity());
   }

   template <typename Func>
   MyMoveOnlyFunction(Func function) noexcept : is_invokable{true}
   {
      static_assert(sizeof(MyMoveOnlyFunctionImpl<Func, ReturnType, Args...>) <=
                        fn.capacity(),
                    "insufficient storage for this implementation");

      std::construct_at(
          reinterpret_cast<MyMoveOnlyFunctionImpl<Func, ReturnType, Args...> *>(
              fn.buffer),
          std::move(function));
   }

   ~MyMoveOnlyFunction()
   {
      if (is_invokable)
         std::destroy_at(fn.ptr());
      is_invokable = false;
   }

   ReturnType operator()(Args... args)
   {
      if (is_invokable)
         return fn.ptr()->operator()(std::forward<Args>(args)...);
      else  // This is a error and should be handled differently
         return ReturnType();
   }

   explicit operator bool() const noexcept
   {
      return is_invokable;
   }

   bool operator==(std::nullptr_t) const noexcept
   {
      return !is_invokable;
   }

   bool operator!=(std::nullptr_t) const noexcept
   {
      return is_invokable;
   }

   MyMoveOnlyFunction &operator=(MyMoveOnlyFunction &&other) noexcept
   {
      MyMoveOnlyFunction temp(std::move(other));
      this->swap(temp);
      return *this;
   }

   void swap(MyMoveOnlyFunction &other) noexcept
   {
      std::swap(is_invokable, other.is_invokable);
      std::swap(this->fn.buffer, other.fn.buffer);
   }

 private:
   using FnStorage = MyMoveOnlyFunctionStorage<
       MyMoveOnlyFunctionInterface<ReturnType, Args...>, size>;

   FnStorage fn;
   bool is_invokable = false;
};

#endif
