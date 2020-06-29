#include <iostream>
#include <unordered_map>
#include <vector>

namespace behavioral {
namespace state_pattern {

enum class State { off_hook, connecting, connected, on_hold, on_hook };

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
  std::unordered_map<State, std::vector<std::pair<Trigger, State>>> rules;

  rules[State::off_hook] = {{Trigger::call_dialed, State::connecting}, {Trigger::stop_using_phone, State::on_hook}};
  rules[State::connecting] = {{Trigger::hung_up, State::off_hook}, {Trigger::call_connected, State::connected}};
  rules[State::connected] = {{Trigger::left_message, State::off_hook}, {Trigger::hung_up, State::off_hook}};
  rules[State::on_hold] = {{Trigger::taken_off_hold, State::connected}, {Trigger::hung_up, State::off_hook}};

  State currentState{State::off_hook};
  State exitState{State::on_hook};

  while (currentState != exitState) {
    std::cout << "The phone is currently " << currentState << std::endl;
    std::cout << "Select a trigger:\n";

    int i = 0;
    for (auto& item : rules[currentState]) {
      std::cout << i++ << ". " << item.first << "\n";
    }

    long unsigned int input;
    input = 1;  // std::cin >> input;
    if ((input + 1) > rules[currentState].size()) {
      std::cout << "Incorrect option. Please try again.\n";
    }

    currentState = rules[currentState][input].second;
  }

  std::cout << "We are done using the phone\n";
}

}  // namespace
