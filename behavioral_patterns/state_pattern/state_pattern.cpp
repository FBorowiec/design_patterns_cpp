/**
 * INTENT:
 * Finite state machines.
 * MOTIVATION:
 * Consider an ordinary telephone:
 * What you do with it depends on the state of the phone/line:
 *  - If it's ringing or you want to make a call, you can pick it up
 *  - Phone must be off the hook to talk/make a call
 *  - If you try to call someone, and it's busy, you put the handset down
 * Changes in state can be explicit or in response to event (Observer pattern).
 *
 * The state pattern is a pattern in which the object's behavior is determined by its state.
 * An object transitions from one state to another (something needs to trigger a transition).
 *
 * A formalized construct which manages state and transitions is called a state machine.
 *
 * Given sufficient complexity, it pays to formally define possible states and events/triggers.
 * Can define:
 *  - State entry/exit behaviors
 *  - Action when a particular event causes a transition
 *  - Guard conditions enabling/disabling are found for an event
 *  - Default action when no transitions are found for an event
 */
#include <iostream>

namespace behavioral {
namespace state_pattern {

/**
 * The traditional approach to the state pattern is not very good.
 * The idea that you have every individual states allowing functions to be called on it,
 * to switch to a completely different state. But the implementation of this function has to
 * end with a 'delete this' which might result in undefined behavior.
 */

class LightSwitch;

struct State {
  virtual void On(LightSwitch* ls) {
    std::cout << "Light is already on.\n";
    auto ls_ = ls;  // unused parameter warning
    (void)ls_;
  }

  virtual void Off(LightSwitch* ls) {
    std::cout << "Light is already off.\n";
    auto ls_ = ls;  // unused parameter warning
    (void)ls_;
  }
};

struct OnState : public State {
  OnState() { std::cout << "Light is turned on!\n"; }

  void Off(LightSwitch* ls) override;
};

struct OffState : public State {
  OffState() { std::cout << "Light is switched off!\n"; }

  void On(LightSwitch* ls) override;
};

class LightSwitch {
 public:
  LightSwitch() { state_ = new OffState(); }

  void SetState(State* state) { this->state_ = state; }

  void On() { state_->On(this); }

  void Off() { state_->Off(this); }

 private:
  State* state_;
};

void OnState::Off(LightSwitch* ls) {
  std::cout << "Switching light off..." << std::endl;
  ls->SetState(new OffState());
  // delete this;
}

void OffState::On(LightSwitch* ls) {
  std::cout << "Switching light on..." << std::endl;
  ls->SetState(new OnState());
  // delete this;
}

}  // namespace state_pattern
}  // namespace behavioral

// TEST---------------------------------------------------------------------------------------------------------------|

#include "gtest/gtest.h"

namespace {

using namespace behavioral::state_pattern;

TEST(StatePatternTest, UsageOfTheStatePattern) {
  LightSwitch ls;
  ls.On();
  ls.Off();
  ls.Off();
}

}  // namespace
