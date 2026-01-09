/*
SPDX-License-Identifier: MIT

Copyright (c) 2026 Bart Bilos
For conditions of distribution and use, see LICENSE file
*/
/**
 * \file test_event_dispatch.cpp
 * Tests for event dispatch
 */

#include "events.hpp"
#include "minunit.h"
#include "ringbuffer.hpp"
#include <array>
#include <span>

struct EventHandler {
   virtual void HandleEvent(EventData event) = 0;
};

struct EventHandlerPair {
   EventHandler *handler;
   Events event;
};

class EventDispatcher
{
 public:
   EventDispatcher(std::span<const EventHandlerPair> event_handlers)
       : handlers(event_handlers)
   {
   }
   ~EventDispatcher()
   {
   }

   void Reset()
   {
      queue.Reset();
   }

   std::size_t GetEventCount()
   {
      return queue.GetLevel();
   }

   void PostEvent(EventData event)
   {
      queue.PushFront(event);
   }

   /**
    * @brief Processes events that are pending
    */
   void Process()
   {
      if (queue.GetLevel() > 0) {
         EventData event;
         queue.PopBack(event);
         for (const EventHandlerPair &handler : handlers) {
            if (handler.event == event.event) {
               handler.handler->HandleEvent(event);
            }
         }
      }
   }

 private:
   RingBuffer<EventData, 10> queue;
   std::span<const EventHandlerPair> handlers;
};

struct ButtonHandler : public EventHandler {
   void HandleEvent(EventData event) override
   {
      event_count++;
      button = event.button;
   }
   std::size_t event_count = 0;
   Button button;
};

struct PowerDownHandler : public EventHandler {
   void HandleEvent(EventData event) override
   {
      event_count++;
      power_down = event.power_down;
   }
   std::size_t event_count = 0;
   PowerDown power_down;
};

struct ErrorHandler : public EventHandler {
   void HandleEvent(EventData event) override
   {
      event_count++;
      error = event.error;
   }
   std::size_t event_count = 0;
   Error error;
};

ButtonHandler button_handler;
PowerDownHandler power_down_handler;
ErrorHandler error_handler;

std::array<const EventHandlerPair, 3> event_handlers{{
    {&button_handler, Events::Button},
    {&power_down_handler, Events::PowerDown},
    {&error_handler, Events::FatalError},
}};

EventDispatcher dut_dispatcher(event_handlers);

MINUNIT_SETUP(EventDispatchSetup)
{
   dut_dispatcher.Reset();
   button_handler.event_count = 0;
   power_down_handler.event_count = 0;
   error_handler.event_count = 0;
   MINUNIT_PASS();
}

MINUNIT_TEARDOWN(EventDispatchTeardown)
{
   MINUNIT_PASS();
}

MINUNIT_ADD(EventDispatchSingleTest, EventDispatchSetup, EventDispatchTeardown)
{
   EventData test_event = {.event = Events::Button, .button = Button::Up};
   dut_dispatcher.PostEvent(test_event);
   MINUNIT_CHECK(dut_dispatcher.GetEventCount() == 1);
   MINUNIT_CHECK(button_handler.event_count == 0);
   dut_dispatcher.Process();
   MINUNIT_CHECK(dut_dispatcher.GetEventCount() == 0);
   MINUNIT_CHECK(button_handler.event_count == 1);
   MINUNIT_CHECK(button_handler.button == Button::Up);
}

MINUNIT_ADD(eventDispatchMultiTest, EventDispatchSetup, EventDispatchTeardown)
{
   EventData test_event_button_up = {.event = Events::Button,
                                     .button = Button::Up};
   EventData test_event_button_down = {.event = Events::Button,
                                       .button = Button::Down};
   EventData test_event_error = {.event = Events::FatalError,
                                 .error = Error::Device};
   dut_dispatcher.PostEvent(test_event_button_up);
   dut_dispatcher.PostEvent(test_event_button_down);
   dut_dispatcher.PostEvent(test_event_error);
   MINUNIT_CHECK(dut_dispatcher.GetEventCount() == 3);
   MINUNIT_CHECK(button_handler.event_count == 0);
   MINUNIT_CHECK(power_down_handler.event_count == 0);
   MINUNIT_CHECK(error_handler.event_count == 0);
   dut_dispatcher.Process();
   MINUNIT_CHECK(dut_dispatcher.GetEventCount() == 2);
   MINUNIT_CHECK(button_handler.event_count == 1);
   MINUNIT_CHECK(button_handler.button == Button::Up);
   MINUNIT_CHECK(power_down_handler.event_count == 0);
   dut_dispatcher.Process();
   MINUNIT_CHECK(dut_dispatcher.GetEventCount() == 1);
   MINUNIT_CHECK(button_handler.event_count == 2);
   MINUNIT_CHECK(button_handler.button == Button::Down);
   MINUNIT_CHECK(power_down_handler.event_count == 0);
   dut_dispatcher.Process();
   MINUNIT_CHECK(dut_dispatcher.GetEventCount() == 0);
   MINUNIT_CHECK(button_handler.event_count == 2);
   MINUNIT_CHECK(power_down_handler.event_count == 0);
   MINUNIT_CHECK(error_handler.event_count == 1);
   MINUNIT_CHECK(error_handler.error == Error::Device);
}