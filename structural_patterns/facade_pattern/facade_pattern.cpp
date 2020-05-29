/**
 * Exposing several components through a single interface.
 * MOTIVATION:
 * It's about balancing complexity and presentation/usability.
 * End user is not exposed to internals - the API user want it to 'just work'.
 *
 * So a Façade provides a simple, easy to understand user interface over a large and sophisticated body of code.
 */
#include <iostream>
#include <memory>

namespace structural {
namespace facade_pattern {

struct Shape {
  virtual void Draw() const = 0;
};

struct Rectangle : public Shape {
  void Draw() const override { std::cout << "Drawing a rectangle...\n"; }
};

struct Square : public Shape {
  void Draw() const override { std::cout << "Drawing a square...\n"; }
};

struct Circle : public Shape {
  void Draw() const override { std::cout << "Drawing a circle...\n"; }
};

// Facade
struct ShapeFacade {
 public:
  ShapeFacade() {
    circle_ = std::make_unique<Circle>();
    square_ = std::make_unique<Square>();
    rectangle_ = std::make_unique<Rectangle>();
  }

  void DrawCircle() { circle_->Draw(); }
  void DrawSquare() { square_->Draw(); }
  void DrawRectangle() { rectangle_->Draw(); }

 private:
  std::unique_ptr<Circle> circle_;
  std::unique_ptr<Square> square_;
  std::unique_ptr<Rectangle> rectangle_;
};

}  // namespace facade_pattern
}  // namespace structural

// TEST---------------------------------------------------------------------------------------------------------------|

#include "gtest/gtest.h"

namespace {

using namespace structural::facade_pattern;

TEST(FacadePatternTest, UsageOfTheFacadePattern) {
  ShapeFacade sf;

  sf.DrawCircle();
  sf.DrawRectangle();
  sf.DrawSquare();
}

}  // namespace
