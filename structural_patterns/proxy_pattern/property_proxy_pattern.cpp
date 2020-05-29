/**
 * Acts as the "getter and setter" for a particular field
 */
#include <iostream>

namespace structural {
namespace proxy_pattern {

template <typename T>
struct Property {
  T value_;

  Property(T value) { *this = value; }

  T operator=(T new_value) {
    std::cout << "Assignment!\n";
    return value_ = new_value;
  }
};

struct Creature {
  Property<int> strenght{10};
  Property<int> agility{10};
};

}  // namespace proxy_pattern
}  // namespace structural

// TEST---------------------------------------------------------------------------------------------------------------|

#include "gtest/gtest.h"

namespace {

using namespace structural::proxy_pattern;

TEST(PropertyProxyPatternTest, UsageOfThePropertyProxyPattern) {
  Creature c;
  c.strenght = 11;
  auto& x = c.agility;
  x = 3;
}

}  // namespace
