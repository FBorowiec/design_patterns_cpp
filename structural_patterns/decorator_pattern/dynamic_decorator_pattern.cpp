/**
 * Adding behavior without altering the class itself.
 * Facilitates the addition of behaviors to individual objects.
 * MOTIVATION:
 *  - Want to augment an object with additional functionality
 *  - Do not want to rewrite or alter existing code (OCP)
 *  - Want to keep new functionality separate (SRP)
 *  - Need to be able to interact with existing structures
 *  Two options:
 *  & Aggregate the decorated object
 *  & Inherit from the decorated object
 *
 * A dynamic decorator keeps the reference to the decorated object(s):
 *  - ColoredShape{Square{}}
 * A static decorator uses mixin inheritance:
 *  - ColoredShape<Square>
 * Both approached allow limitless composition:
 *  - TranspareShape<ColoredShape<Circle>>
 */
#include <iostream>
#include <sstream>
#include <string>

namespace structural {
namespace decorator_pattern {

struct Shape {
  virtual std::string Str() const = 0;
};

struct Circle : public Shape {
 public:
  Circle() {}
  Circle(float radius) : radius_(radius) {}

  void Resize(float factor) { radius_ *= factor; }

  std::string Str() const override {
    std::ostringstream oss;
    oss << "A circle of radius " << radius_;
    return oss.str();
  }

 private:
  float radius_;
};

struct Square : public Shape {
 public:
  Square() {}
  Square(float side) : side_(side) {}

  std::string Str() const override {
    std::ostringstream oss;
    oss << "A square with side " << side_;
    return oss.str();
  }

 private:
  float side_;
};

// Decorator with new functionality
struct ColoredShape : public Shape {
 public:
  ColoredShape(Shape& shape, const std::string& color) : shape_(shape), color_(color) {}

  std::string Str() const override {
    std::ostringstream oss;
    oss << shape_.Str() << " has the color " << color_;
    return oss.str();
  }

 private:
  Shape& shape_;
  std::string color_;
};

// Another decorator
struct TransparentShape : public Shape {
 public:
  TransparentShape(Shape& shape, const uint8_t transparency_value)
      : shape_(shape), transparency_value_(transparency_value) {}

  std::string Str() const override {
    std::ostringstream oss;
    oss << shape_.Str() << " has " << static_cast<float>(transparency_value_) / 255.f * 100.f << "% transparency";
    return oss.str();
  }

 private:
  Shape& shape_;
  uint8_t transparency_value_;
};

}  // namespace decorator_pattern
}  // namespace structural

// TEST---------------------------------------------------------------------------------------------------------------|

#include "gtest/gtest.h"

namespace {

using namespace structural::decorator_pattern;

TEST(DecoratorPatternTest, UsageOfTheDecoratorPattern) {
  Square square{5};
  ColoredShape red_square{square, "red"};
  std::cout << square.Str() << std::endl << red_square.Str() << std::endl;
}

TEST(DecoratorPatternTest, AggregatingTwoDecorators) {
  Square square{5};
  ColoredShape red_square{square, "red"};

  TransparentShape my_square{red_square, 51};
  std::cout << my_square.Str() << std::endl;
}

/**
 * This approach has a certain limitation which is that the Circle has a method called resize.
 * Resize isn't part of the Shape interface.
 * So it doesn't allowed to access the underlying API of whatever object we're decorating,
 * unless it's part of some interface.
 */

}  // namespace
