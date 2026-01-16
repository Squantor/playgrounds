/*
SPDX-License-Identifier: MIT

Copyright (c) 2026 Bart Bilos
For conditions of distribution and use, see LICENSE file
*/
/**
 * \file buttons.hpp
 * Translation class from buttons to events
 */
#ifndef BUTTONS_HPP
#define BUTTONS_HPP

#include "event_dispatch.hpp"
#include "events.hpp"
#include "application.hpp"

class Buttons {
 public:
  Buttons(std::uint8_t default_pin_state, EventDispatcher& dispatcher)
    : pin_state(default_pin_state), event_dispatcher(dispatcher) {}

  void SetPortData(std::uint8_t data) {
    std::uint8_t changed = data ^ pin_state;
    if ((changed & 0x01) != 0) {
      if (data & 0x01) {
        event_dispatcher.PostEvent(EventData{Events::Button, Button::Button0Up});
      } else {
        event_dispatcher.PostEvent(EventData{Events::Button, Button::Button0Down});
      }
    }
    if ((changed & 0x02) != 0) {
      if (data & 0x02) {
        event_dispatcher.PostEvent(EventData{Events::Button, Button::Button1Up});
      } else {
        event_dispatcher.PostEvent(EventData{Events::Button, Button::Button1Down});
      }
    }
    if ((changed & 0x04) != 0) {
      if (data & 0x04) {
        event_dispatcher.PostEvent(EventData{Events::Button, Button::Button2Up});
      } else {
        event_dispatcher.PostEvent(EventData{Events::Button, Button::Button2Down});
      }
    }
    if ((changed & 0x08) != 0) {
      if (data & 0x08) {
        event_dispatcher.PostEvent(EventData{Events::Button, Button::Button3Up});
      } else {
        event_dispatcher.PostEvent(EventData{Events::Button, Button::Button3Down});
      }
    }
    if ((changed & 0x10) != 0) {
      if (data & 0x10) {
        event_dispatcher.PostEvent(EventData{Events::Button, Button::Button4Up});
      } else {
        event_dispatcher.PostEvent(EventData{Events::Button, Button::Button4Down});
      }
    }
    // update internal state
    pin_state = data;
  }

 private:
  std::uint8_t pin_state;
  EventDispatcher& event_dispatcher;
};

#endif