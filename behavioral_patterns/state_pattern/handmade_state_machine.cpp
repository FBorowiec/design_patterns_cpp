#include <iostream>

namespace behavioral {
namespace state_pattern {

enum class State {
  off_hook,
  connecting,
  connected,
  on_hold,
  on_hook
};

inline std::ostream& operator<<(std::ostream& os, const State& s) {
  switch (s) {
    case State::off_hook:
      os << "Off the hook";
      break;
    case State::connecting:
      os << "Connecting";
      break;
    case State::connected:
      os << "Connected";
      break;
    case State::on_hold:
      os << "On hold";
      break;
    case State::on_hook:
      os << "On hook";
      break;
  }
  return os;
}

enum class Trigger {
  call_dialed,
  hung_up,
  call_connected,
  placed_on_hold,
  taken_off_hold,
  left_message,
  stop_using_phone
};


inline std::ostream& operator<<(std::ostream& os, const Trigger& t) {
  switch (t) {
    case Trigger::call_dialed:
      os << "Call dialed";
      break;
    case Trigger::hung_up:
      os << "Hung up";
      break;
    case Trigger::call_connected:
      os << "Call connected";
      break;
    case Trigger::placed_on_hold:
      os << "Placed n hold";
      break;
    case Trigger::taken_off_hold:
      os << "Taken off hold";
      break;
    case Trigger::left_message:
      os << "Left message";
      break;
    case Trigger::stop_using_phone:
      os << "Stop using phone";
      break;
  }
  return os;
}

}  // namespace state_pattern
}  // namespace behavioral

// TEST---------------------------------------------------------------------------------------------------------------|

#include "gtest/gtest.h"

namespace {

using namespace behavioral::state_pattern;

TEST(StatePatternTest, UsageOfTheStatePattern) {
  
}

}  // namespace
