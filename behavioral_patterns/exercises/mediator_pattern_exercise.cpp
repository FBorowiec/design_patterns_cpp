/**
 * Our system has any number of instances of Participant classes.
 * Each Participant has a value integer, initially zero.
 * A participant can say() a particular value, which is broadcast to all other participants. At this point in time,
 * every other participant is obliged to increase their value by the value being broadcast.
 *
 * Example:
 *  - Two participants start with values 0 and 0 respectively.
 *  - Participant 1 broadcasts the value 3. We now have Participant 1 value - 0, Participant 2 value = 3
 *  - Participant 2 broadcasts the value 2. We now have Participant 1 value - 2, Participant 2 value = 3
 */
#include <vector>

namespace behavioral {
namespace mediator_pattern_exercise {

struct IParticipant {
  virtual void notify(IParticipant* sender, int value) = 0;
};

struct Mediator {
  std::vector<IParticipant*> participants;
  void say(IParticipant* sender, int value) {
    for (auto p : participants) p->notify(sender, value);
  }
};

struct Participant : IParticipant {
  int value_{0};
  Mediator& mediator_;

  Participant(Mediator& mediator) : mediator_(mediator) { mediator_.participants.push_back(this); }

  void notify(IParticipant* sender, int value) override {
    if (sender != this) this->value_ += value;
  }

  void say(int value) { mediator_.say(this, value); }
};

}  // namespace mediator_pattern_exercise
}  // namespace behavioral

// TEST---------------------------------------------------------------------------------------------------------------|
#include "gtest/gtest.h"

namespace {

using namespace behavioral::mediator_pattern_exercise;

TEST(MediatorPatternExerciseTest, SimpleTest) {
  Mediator m;
  Participant p1{m}, p2{m};

  ASSERT_EQ(0, p1.value_);
  ASSERT_EQ(0, p2.value_);

  p1.say(2);

  ASSERT_EQ(0, p1.value_);
  ASSERT_EQ(2, p2.value_);

  p2.say(4);

  ASSERT_EQ(4, p1.value_);
  ASSERT_EQ(2, p2.value_);
}

}  // namespace
