/**
 * You are given a game scenario with classes Goblin and GoblinKing.
 * Implement the following rules:
 *  - A Goblin has base 1 attack / 1 defence (1/1), a Goblin King is 3/3.
 *  - When the Goblin Kind is in play, every other Goblin gets +1 Attack.
 *  - Goblins get +1 Defence sor every other Goblin in play (a GoblinKing is a Goblin).
 *
 * Examples:
 *  - Suppose you have 3 ordinary Goblins in play. Each one is a 1/3 (1/1 + 0/2 defence bonus).
 *  - A Goblin King comes into play.
 *    Now every ordinary Goblin is a 2/4 (1/1 + 0/3 defence bonus from each other + 1/0 from Goblin King).
 *  - Meanwhile, the Goblin King itself is 3/6 (3/3 + 0/3 defence bonus from other Goblins).
 *
 * Here is an example of the kind of test that will be run on the system:
 *
 * Game game;
 * Goblin goblin{game};
 * game.creatures.push_back(&goblin);
 * ASSERT_EQ(1, goblin.get_attack());
 * ASSERT_EQ(1, goblin.get_defence());
 */
#include <vector>

namespace behavioral {
namespace chain_of_responsibility_pattern_exercise {

struct Creature;

struct Game {
  std::vector<Creature *> creatures;
};

struct StatQuery {
  enum Statistic { attack, defense } statistic;
  int result;
};

struct Creature {
 public:
  Creature(Game &game, int base_attack, int base_defense)
      : game_(game), base_attack_(base_attack), base_defense_(base_defense) {}
  virtual int get_attack() = 0;
  virtual int get_defense() = 0;
  virtual void query(void *source, StatQuery &sq) = 0;

 protected:
  Game &game_;
  int base_attack_, base_defense_;
};

class Goblin : public Creature {
 public:
  Goblin(Game &game, int base_attack, int base_defense) : Creature(game, base_attack, base_defense) {}

  Goblin(Game &game) : Creature(game, 1, 1) {}

  int get_statistic(StatQuery::Statistic stat) {
    StatQuery q{stat, 0};
    for (auto c : game_.creatures) c->query(this, q);
    return q.result;
  }

  int get_attack() override { return get_statistic(StatQuery::attack); }

  int get_defense() override { return get_statistic(StatQuery::defense); }

  void query(void *source, StatQuery &sq) override {
    if (source == this) {
      switch (sq.statistic) {
        case StatQuery::attack:
          sq.result += base_attack_;
          break;
        case StatQuery::defense:
          sq.result += base_defense_;
          break;
      }
    } else {
      if (sq.statistic == StatQuery::defense) {
        sq.result++;
      }
    }
  }
};

class GoblinKing : public Goblin {
 public:
  GoblinKing(Game &game) : Goblin(game, 3, 3) {}

  void query(void *source, StatQuery &sq) override {
    if (source != this && sq.statistic == StatQuery::attack) {
      sq.result++;
    } else
      Goblin::query(source, sq);
  }
};

}  // namespace chain_of_responsibility_pattern_exercise
}  // namespace behavioral

// TEST---------------------------------------------------------------------------------------------------------------|
#include <iostream>
#include "gtest/gtest.h"

namespace {

using namespace behavioral::chain_of_responsibility_pattern_exercise;

TEST(ChainOfResponsibilityPatternExerciseTest, SimpleTest) {
  Game game;
  Goblin goblin{game};
  game.creatures.push_back(&goblin);

  std::cout << "Checking that a baseline goblin is a 1/1...\n";

  EXPECT_EQ(1, goblin.get_attack());
  EXPECT_EQ(1, goblin.get_defense());

  std::cout << "Adding a second goblin, now they should be 1/2...\n";
  Goblin goblin2{game};
  game.creatures.push_back(&goblin2);

  EXPECT_EQ(1, goblin.get_attack());
  EXPECT_EQ(2, goblin.get_defense());

  std::cout << "Adding a goblin king, now a goblin should be 2/3...\n";
  GoblinKing goblin3{game};
  game.creatures.push_back(&goblin3);

  EXPECT_EQ(2, goblin.get_attack());
  EXPECT_EQ(3, goblin.get_defense());
}

}  // namespace
