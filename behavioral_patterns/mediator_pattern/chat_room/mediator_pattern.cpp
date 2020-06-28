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
 *
 * IMPLEMENTATION:
 * 1. Create the mediator and have each object in the system refer to it: eg. in a field.
 * 2. Mediator engages in bidirectional communication with its connected components.
 * 3. Mediator has functions the components can call.
 * 4. Components have functions the mediator can call.
 * 5. Event processing (e.g., Rx) libraries make communication easier to implement.
 */
#include "chat_room.hpp"
#include "person.hpp"

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
