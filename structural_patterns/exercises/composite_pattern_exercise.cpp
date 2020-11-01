/**
 * Consider the code presented below. The sum() function takes a vector of pointers to either SingleValue or ManyValues
 * instances and adds up all their elements together. Complete the implementation so that the sum() function starts to
 * operate correctly. This may involve giving the classes a common interface, among other things.
 *
 * Here is an example of how the function might be used:
 *
 * SingleValue single_value{1};
 * ManyValues other_values;
 * other_values.add(2);
 * other_values.add(3);
 * sum({&single_value, &other_values});  // returns 6
 */
#include <numeric>
#include <vector>

namespace structural {
namespace composite_pattern_exercise {

struct ContainsIntegers {
  virtual int Sum() = 0;
};

struct SingleValue : public ContainsIntegers {
  SingleValue() = default;

  explicit SingleValue(const int value) : value_(value) {}

  int Sum() override { return value_; }

  int value_{0};
};

struct ManyValues : std::vector<int>, ContainsIntegers {
  void Add(const int value) { push_back(value); }

  int Sum() override { return std::accumulate(begin(), end(), 0); }
};

int Sum(const std::vector<ContainsIntegers*> items) {
  int result{0};
  for (auto item : items) result += item->Sum();
  return result;
}

}  // namespace composite_pattern_exercise
}  // namespace structural

// TEST---------------------------------------------------------------------------------------------------------------|
#include "gtest/gtest.h"

namespace {

using namespace structural::composite_pattern_exercise;

TEST(CompositePatternExerciseTest, SimpleTest) {
  SingleValue single_value{11};
  ManyValues other_values;
  other_values.Add(22);
  other_values.Add(33);
  ASSERT_EQ(66, Sum({&single_value, &other_values}));
}

}  // namespace
