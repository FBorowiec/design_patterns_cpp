/**
 * Roses can be red, blue or red and blue. Given the class interface Flower and class Rose, build decorators RedFlower
 * and BlueFlower that would print the following:
 *
 * Rose ros;
 * RedFlower red_rose{rose};
 * RedFlower red_red_rose{red_rose};
 * BlueFlower blue_red_rose{red_rose};
 * std::cout << rose.str()             // "A rose"
 * std::cout << red_rose.str()         // "A rose that is red"
 * std::cout << red_red_rose.str()     // "A rose that is red"
 * std::cout << blue_red_rose.str()    // "A rose that is red and blue"
 */
#include <string>

namespace structural {
namespace decorator_pattern_exercise {

struct Flower {
  virtual std::string str() = 0;
};

struct Rose : Flower {
  std::string str() override { return "A rose"; }
};

struct RedFlower : Flower {
  std::string str() override {
    std::string s = flower_.str();

    if (s.find("red") != std::string::npos)
      return s;
    else if (s.find("blue") != std::string::npos) {
      return s + " and red";
    } else
      return s + " that is red";
  }

  Flower& flower_;
  RedFlower(Flower& flower) : flower_(flower) {}
};

struct BlueFlower : Flower {
  std::string str() override {
    std::string s = flower_.str();

    if (s.find("blue") != std::string::npos)
      return s;
    else if (s.find("red") != std::string::npos) {
      return s + " and blue";
    } else
      return s + " that is blue";
  }

  Flower& flower_;
  BlueFlower(Flower& flower) : flower_(flower) {}
};

}  // namespace decorator_pattern_exercise
}  // namespace structural

// TEST---------------------------------------------------------------------------------------------------------------|
#include "gtest/gtest.h"

namespace {

using namespace structural::decorator_pattern_exercise;

class DecoratorPatternExerciseTest : public testing::Test {
 public:
  Rose rose;
  BlueFlower blue_rose{rose};
  RedFlower red_rose{rose};
};

TEST_F(DecoratorPatternExerciseTest, BaselineTest) { ASSERT_EQ("A rose", Rose{}.str()); }

TEST_F(DecoratorPatternExerciseTest, SingleColorTests) {
  ASSERT_EQ("A rose that is blue", blue_rose.str());
  ASSERT_EQ("A rose that is red", red_rose.str());
}

TEST_F(DecoratorPatternExerciseTest, RepetitionTest) {
  ASSERT_EQ("A rose that is red", RedFlower{red_rose}.str())
      << "This rose was made red twice, but you should print once.";
}

TEST_F(DecoratorPatternExerciseTest, MultiColorTests) {
  ASSERT_EQ("A rose that is red and blue", BlueFlower{red_rose}.str());
  ASSERT_EQ("A rose that is blue and red", RedFlower{blue_rose}.str());
}

TEST_F(DecoratorPatternExerciseTest, NestedRepetitionTest) {
  BlueFlower b_r_rose{red_rose};
  RedFlower r_b_r_rose{b_r_rose};
  ASSERT_EQ("A rose that is red and blue", r_b_r_rose.str()) << "This is a complicated case. I'm expecting that "
                                                             << "a rose defined as Red{Blue{Red{Rose{}}}} is printed "
                                                             << "as 'red and blue'.";
}

}  // namespace
