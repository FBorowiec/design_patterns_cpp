#include "event_broker.hpp"

// TEST---------------------------------------------------------------------------------------------------------------|

#include "gtest/gtest.h"

namespace {

using namespace behavioral::mediator_pattern;

TEST(MediatorPatternTest, UsageOfTheMediatorPatternForEventBroker) {
  Game game;
  Player player{"Sam", game};
  Coach coach{game};

  player.Score();
  player.Score();
  player.Score();
}

}  // namespace
