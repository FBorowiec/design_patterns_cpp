/**
 * Imagine a typical collectible card game which has cards representing creatures. Each creature has two values: Attack
 * and Health. Creatures can fight each other, dealing their Attack damage, thereby reducing their opponent's health.
 *
 * The class CardGame implements the logic for two creature fighting one another. However, the exact mechanics of how
 * damage is dealt is different:
 *  - TemporaryCardDamage: In some games (e.g., Magic: the Gathering), unless the creature has been killed, its health
 *    returns to the original value at the end of combat.
 *  - PermanentCardDamage: In other games (e.g., HearthStone), health damage persists.
 *
 * Implement classes TemporaryCardDamageGame and PermanentCardDamageGame that would allow us to simulate combat between
 * creatures.
 *
 * Examples:
 *  - With temporary damage, creatures 1/2 and 1/3 can never kill one another. With permanent damage, second creature
 *    will win after 2 rounds of combat.
 *  - With either temporary or permanent damage, two 2/2 creatures kill one another.
 */
#include <vector>

namespace behavioral {
namespace template_method_exercise {

struct Creature {
  Creature(int attack, int health) : attack_(attack), health_(health) {}

  int attack_, health_;
};

struct CardGame {
  CardGame(const std::vector<Creature> &creatures) : creatures_(creatures) {}

  // return the index of the creature that won (is a live)
  // example:
  // - creature1 alive, creature2 dead, return creature1
  // - creature1 dead, creature2 alive, return creature2
  // - no clear winner: return -1
  int combat(int creature1, int creature2) {
    Creature &first = creatures_[static_cast<long unsigned int>(creature1)];
    Creature &second = creatures_[static_cast<long unsigned int>(creature2)];
    hit(first, second);
    hit(second, first);
    bool first_alive = first.health_ > 0;
    bool second_alive = second.health_ > 0;
    if (first_alive == second_alive) return -1;
    return first_alive ? creature1 : creature2;
  }

  virtual void hit(Creature &attacker, Creature &other) = 0;

  std::vector<Creature> creatures_;
};

struct TemporaryCardDamageGame : CardGame {
  TemporaryCardDamageGame(const std::vector<Creature> &creatures) : CardGame(creatures) {}

  void hit(Creature &attacker, Creature &other) override {
    auto old_health = other.health_;
    other.health_ -= attacker.attack_;
    if (other.health_ > 0) other.health_ = old_health;
  }
};

struct PermanentCardDamageGame : CardGame {
  PermanentCardDamageGame(const std::vector<Creature> &creatures) : CardGame(creatures) {}

  void hit(Creature &attacker, Creature &other) override { other.health_ -= attacker.attack_; }
};

}  // namespace template_method_exercise
}  // namespace behavioral

// TEST---------------------------------------------------------------------------------------------------------------|
#include "gtest/gtest.h"

namespace {

using namespace behavioral::template_method_exercise;

TEST(TemplateMethodExerciseTest, ImpasseTest) {
  Creature c1{1, 2};
  Creature c2{1, 2};
  TemporaryCardDamageGame game({c1, c2});
  ASSERT_EQ(-1, game.combat(0, 1));
  ASSERT_EQ(-1, game.combat(0, 1));
}

TEST(TemplateMethodExerciseTest, TemporaryMurderTest) {
  Creature c1{1, 1};
  Creature c2{2, 2};
  TemporaryCardDamageGame game({c1, c2});
  ASSERT_EQ(1, game.combat(0, 1));
}

TEST(TemplateMethodExerciseTest, DoubleMurderTest) {
  Creature c1{2, 2};
  Creature c2{2, 2};
  TemporaryCardDamageGame game({c1, c2});
  ASSERT_EQ(-1, game.combat(0, 1)) << "The expectation here is that two 2/2 creatures kill each other";
}

TEST(TemplateMethodExerciseTest, PermanentDamageDeathTest) {
  Creature c1{1, 2};
  Creature c2{1, 3};
  PermanentCardDamageGame game({c1, c2});
  ASSERT_EQ(-1, game.combat(0, 1)) << "1/2 vs 1/3 should have no winner after first round of combat";
  ASSERT_EQ(1, game.combat(0, 1)) << "1/1 vs 1/2 here, so winner should be = 1";
}

}  // namespace
