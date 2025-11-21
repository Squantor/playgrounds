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

#include <memory>
#include <utility>

struct MyFunctionSomeClass {
};

union MyFunctionUnion {
   void *some_ptr;
   void (*some_func)();
   void (MyFunctionSomeClass::*some_member_func)();
};

template <typename T, std::size_t size> struct MyFunctionStorage {
   static constexpr auto capacity()
   {
      return size;
   }

   union {
      MyFunctionUnion mfu;
      std::byte buffer[capacity()];
   };

   auto ptr()
   {
      return reinterpret_cast<T *>(&buffer);
   }

   MyFunctionStorage() = default;
   MyFunctionStorage(const MyFunctionStorage &) = delete;
   MyFunctionStorage &operator=(const MyFunctionStorage &) = delete;
};

template <typename ReturnType, typename... Args> struct MyFunctionInterface {
   virtual ~MyFunctionInterface() = default;
   virtual ReturnType operator()(Args...) = 0;
};

template <typename Fn, typename ReturnType, typename... Args>
class MyFunctionImpl : public MyFunctionInterface<ReturnType, Args...>
{
   Fn fn;

 public:
   MyFunctionImpl(Fn fn) : fn(std::move(fn))
   {
   }

   ReturnType operator()(Args... args) override
   {
      return fn(std::forward<Args>(args)...);
   }
};

template <typename, size_t = 32> class MyFunction;

template <typename ReturnType, typename... Args, std::size_t size>
class MyFunction<ReturnType(Args...), size>
{
   MyFunctionStorage<MyFunctionInterface<ReturnType, Args...>, size> fn;

 public:
   template <typename Func> MyFunction(Func function)
   {
      static_assert(sizeof(MyFunctionImpl<Func, ReturnType, Args...>) <=
                        fn.capacity(),
                    "insufficient storage for this implementation");
      std::construct_at(
          reinterpret_cast<MyFunctionImpl<Func, ReturnType, Args...> *>(
              fn.buffer),
          std::move(function));
   }

   ~MyFunction()
   {
      std::destroy_at(fn.ptr());
   }

   ReturnType operator()(Args... args)
   {
      return fn.ptr()->operator()(std::forward<Args>(args)...);
   }
};

#endif
