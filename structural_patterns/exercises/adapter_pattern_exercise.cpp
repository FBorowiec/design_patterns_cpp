/**
 * You are given a Rectangle protocol and an extension method on it.
 * Try to define a SquareToRectangleAdapter that adapts the Square to the Rectangle interface.
 */
#include <functional>

namespace structural {
namespace adapter_pattern_exercise {

struct Square {
  explicit Square(const int side) : side_(side) {}

  int side_{0};
};

struct Rectangle {
  virtual int width() const = 0;
  virtual int height() const = 0;

  int area() const { return width() * height(); }
};

struct SquareToRectangleAdapter : Rectangle {
  SquareToRectangleAdapter(const Square& square) : square_(square) {}
  int width() const override { return square_.side_; }
  int height() const override { return square_.side_; }

  const Square& square_;
};

}  // namespace adapter_pattern_exercise
}  // namespace structural

// TEST---------------------------------------------------------------------------------------------------------------|
#include "gtest/gtest.h"

namespace {

using namespace structural::adapter_pattern_exercise;

TEST(SquareToRectangleAdapterTest, SimpleTest) {
  Square sq{11};
  SquareToRectangleAdapter adapter{sq};
  ASSERT_EQ(121, adapter.area());
}

}  // namespace
