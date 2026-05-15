/*
SPDX-License-Identifier: MIT

Copyright (c) 2026 Bart Bilos
For conditions of distribution and use, see LICENSE file
*/
/**
 * \file event_dispatch.hpp
 * Event dispatcher definitions
 */
#ifndef EVENT_DISPATCH_HPP
#define EVENT_DISPATCH_HPP

#include "events.hpp"
#include "event_handler.hpp"

struct EventHandlerPair {
  Event_handler *handler;
  Events event;
};

class EventDispatcher {
 public:
  EventDispatcher(std::span<const EventHandlerPair> event_handlers) : handlers(event_handlers) {}

  void Reset() {
    queue.reset();
  }

  std::size_t GetEventCount() {
    return queue.get_level();
  }

  void PostEvent(Event_data event) {
    queue.push_front(event);
  }

  /**
   * @brief Processes events that are pending
   */
  void Process() {
    if (queue.get_level() > 0) {
      Event_data event;
      queue.pop_back(event);
      for (const EventHandlerPair &handler : handlers) {
        if (handler.event == event.event) {
          handler.handler->handle_event(event);
        }
      }
    }
  }

 private:
  libmcu::Ring_buffer<Event_data, 10, libmcu::Assert_trap> queue;
  std::span<const EventHandlerPair> handlers;
};

#endif
