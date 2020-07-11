/**
 * INTENT:
 * System behavior partially specified at runtime.
 * MOTIVATION:
 * Many algorithms can be decomposed into higher- and lower-level parts ex:
 *  Making tea can be decomposed:
 *  - Boil water, pour into cup
 *  - Tea specific things (teabag into water)
 *  The high-level algorithm can ten be reused for making another beverage.
 *
 * The strategy design pattern enables the exact behavior of a system to be selected
 * either at run-time (dynamic) or compile-time (static).
 * Also know as the Policy design patterns.
 */
#include <iostream>

namespace behavioral {
namespace strategy_pattern {

enum class OutpuFormat {
  markdown,
  // * item1
  // * item2

  html
  // <ul>
  //  <li>item1</li>
  // </ul>
};

struct ListStrategy {
  virtual void Start(std::ostringstream& oss) {}
  virtual void End(std::ostringstream& oss) {}
  virtual void AddListItem(std::ostringstream& oss, const std::string& item) = 0;
};



}  // namespace strategy_pattern
}  // namespace behavioral

// TEST---------------------------------------------------------------------------------------------------------------|

#include "gtest/gtest.h"

namespace {

using namespace behavioral::strategy_pattern;

TEST(StrategyPatternTest, UsageOfTheStrategyPattern) {
}

}  // namespace
