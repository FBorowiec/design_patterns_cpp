/**
 * Imagine a game where one or more rats can attack a player. Each individual rat has an attack value of 1.
 * However, rats attack as a swarm, so each rat's attack value is equal to the total number of rats in play.
 *
 * Given that a rat enters play through the constructor and leaves play (dies) via its destructor, please implement the
 * Game and Rat classes so that, at any point in the game, the attack value of a rat is always consistent.
 */
#include <algorithm>
#include <vector>

namespace behavioral {
namespace observer_pattern_exercise {

struct IRat {
  virtual void rat_enters(IRat* sender) = 0;
  virtual void rat_dies(IRat* sender) = 0;
  virtual void notify(IRat* target) = 0;
};

struct Game {
  virtual void fire_rat_enters(IRat* sender) {
    for (auto rat : rats) rat->rat_enters(sender);
  }
  virtual void fire_rat_dies(IRat* sender) {
    for (auto rat : rats) rat->rat_dies(sender);
  }
  virtual void fire_notify(IRat* target) {
    for (auto rat : rats) rat->notify(target);
  }

  std::vector<IRat*> rats;
};

struct Rat : IRat {
  Rat(Game& game) : game_(game) {
    game_.rats.push_back(this);
    game_.fire_rat_enters(this);
  }

  ~Rat() {
    game_.fire_rat_dies(this);
    game_.rats.erase(std::remove(game_.rats.begin(), game_.rats.end(), this));
  }

  void rat_enters(IRat* sender) override {
    if (sender != this) {
      ++attack;
      game_.fire_notify(sender);
    }
  }

  void rat_dies(IRat* sender) override {
    (void)sender;
    --attack;
  }

  void notify(IRat* target) override {
    if (target == this) ++attack;
  }

  Game& game_;
  int attack{1};
};

}  // namespace observer_pattern_exercise
}  // namespace behavioral

// TEST---------------------------------------------------------------------------------------------------------------|
#include "gtest/gtest.h"

namespace {

using namespace behavioral::observer_pattern_exercise;

TEST(ObserverPatternExerciseTest, SingleRatTest) {
  Game game;
  Rat rat{game};
  ASSERT_EQ(1, rat.attack);
}

TEST(ObserverPatternExerciseTest, TwoRatTest) {
  Game game;
  Rat rat{game};
  Rat rat2{game};
  ASSERT_EQ(2, rat.attack);
  ASSERT_EQ(2, rat2.attack);
}

TEST(ObserverPatternExerciseTest, ThreeRatsOneDies) {
  Game game;
  Rat rat{game};
  ASSERT_EQ(1, rat.attack);

  Rat rat2{game};
  ASSERT_EQ(2, rat.attack);
  ASSERT_EQ(2, rat2.attack);

  {
    Rat rat3{game};

    ASSERT_EQ(3, rat.attack);
    ASSERT_EQ(3, rat2.attack);
    ASSERT_EQ(3, rat3.attack);
  }

  ASSERT_EQ(2, rat.attack);
  ASSERT_EQ(2, rat2.attack);
}

}  // namespace
