/**
 * Implement Line::deep_copy() to perform a deep copy of the current Line object.
 * Beware memory leaks!
 */
namespace creational {
namespace prototype_pattern_exercise {

struct Point {
  int x_{0}, y_{0};

  Point() {}

  Point(const int x, const int y) : x_{x}, y_{y} {}
};

struct Line {
  Point *start_, *end_;

  Line(Point* const start, Point* const end) : start_(start), end_(end) {}

  ~Line() {
    delete start_;
    delete end_;
  }

  Line deep_copy() const { return Line{new Point(start_->x_, start_->y_), new Point(end_->x_, end_->y_)}; }
};

}  // namespace prototype_pattern_exercise
}  // namespace creational

// TEST---------------------------------------------------------------------------------------------------------------|
#include "gtest/gtest.h"

namespace {

using namespace creational::prototype_pattern_exercise;

TEST(Evaluate, SimpleTest) {
  Line line1{new Point{3, 3}, new Point{10, 10}};

  auto line2 = line1.deep_copy();
  line1.start_->x_ = line1.start_->y_ = line1.end_->y_ = 0;

  ASSERT_EQ(3, line2.start_->x_);
  ASSERT_EQ(3, line2.start_->y_);
  ASSERT_EQ(10, line2.end_->x_);
  ASSERT_EQ(10, line2.end_->y_);
}

}  // namespace