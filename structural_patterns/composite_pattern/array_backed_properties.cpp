#include <algorithm>
#include <array>
#include <cmath>
#include <iostream>
#include <numeric>

namespace structural {
namespace composite_pattern {

namespace bad {

/**
 * This approach is ugly and doesn't scale.
 * If you were to add a new property like charisma,
 * it would be very tedious to actually implement all these calculations.
 * Every single aggregate like sum(), average() and max() would need to be rewritten.
 */
class Creature {
 public:
  int get_strength() const { return strength_; }
  void set_strength(int strength) { Creature::strength_ = strength; }

  int get_agility() const { return agility_; }
  void set_agility(int agility) { Creature::agility_ = agility; }

  int get_intelligence() const { return intelligence_; }
  void set_intelligence(int intelligence) { Creature::intelligence_ = intelligence; }

  // sum, average, max.
  double sum() const { return strength_ + agility_ + intelligence_; }
  double average() const { return sum() / 3.0; }
  int max() const { return std::max(std::max(strength_, agility_), intelligence_); }

 private:
  int strength_, agility_, intelligence_;
  // new property
  int charisma;
};

}  // namespace bad

namespace good {

/**
 * The solution to this problem is to have aggregate storage (composites).
 * C++ uses "duck typing", expecting enumerable (enum Agilities) types to provide begin() and end().
 */
class Creature {
 public:
  int GetStrength() const { return abilities[strength]; }
  void SetStrength(int value) { abilities[strength] = value; }

  int GetAgility() const { return abilities[agility]; }
  void SetAgility(int value) { abilities[agility] = value; }

  int GetIntelligence() const { return abilities[intelligence]; }
  void SetIntelligence(int value) { abilities[intelligence] = value; }

  int Sum() const { return std::accumulate(abilities.begin(), abilities.end(), 0); }
  double Average() const { return Sum() / static_cast<double>(count); }
  int Max() const { return *std::max_element(abilities.begin(), abilities.end()); }

 private:
  enum Abilities { strength, agility, intelligence, count };
  std::array<int, count> abilities;
};

}  // namespace good

}  // namespace composite_pattern
}  // namespace structural

// TEST---------------------------------------------------------------------------------------------------------------|

#include "gtest/gtest.h"

namespace {

using namespace structural::composite_pattern::good;

TEST(CompositePatternArrayBackedProperties, UsageOfTheCompositePattern) {
  Creature orc;
  orc.SetStrength(16);
  orc.SetAgility(11);
  orc.SetIntelligence(9);

  std::cout << "The orc has an average stat of: " << orc.Average() << " and a maximum stat of " << orc.Max() << "\n";
}

}  // namespace
