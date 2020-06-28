/**
 * Facilitates communication between components.
 * MOTIVATION:
 * Components may go in and out of a system at any time:
 *  - Chat room particitpants
 *  - Players in an MMORPG
 * It makes no sense for them to have direct references to one another:
 *  - Those references may go dead at any time
 * SOLUTION:
 * Have them all refer to some central component that facilitates communication
 *
 * The Mediator is therefore a component that facilitates communication between each
 * other components without them necessarily being aware of each otehr or having
 * direct (reference) access to each other.
 */
#include "person.hpp"
#include "chat_room.hpp"

// TEST---------------------------------------------------------------------------------------------------------------|

#include "gtest/gtest.h"

namespace {

using namespace behavioral::mediator_pattern;

TEST(MediatorPatternTest, UsageOfTheMediatorPattern) {
  ChatRoom room;

  Person john{"John"};
  Person jane{"Jane"};

  room.Join(&john);
  room.Join(&jane);

  john.Say("Hi room!");
  jane.Say("oh, hey John!");

  Person simon{"Simon"};
  room.Join(&simon);

  simon.Say("Hi everybody!");

  jane.Pm("Simon", "Glag you've found us Simon!");
}

}  // namespace
