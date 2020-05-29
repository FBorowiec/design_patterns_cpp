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
 */
#include <iostream>
#include <sstream>
#include <string>

namespace structural {
namespace decorator_pattern {
namespace static_decorator {

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

template <typename T>
struct ColoredShape2 : T {
 public:
  static_assert(std::is_base_of<Shape, T>::value, "Template argument must be a Shape");

  ColoredShape2() {}

  template <typename... Args>
  ColoredShape2(const std::string color, Args... args) : T(std::forward<Args>(args)...), color_(color) {}

  std::string Str() const override {
    std::ostringstream oss;
    oss << T::Str() << " has the color " << color_;
    return oss.str();
  }

 private:
  std::string color_;
};

template <typename T>
struct TransparentShape2 : T {
 public:
  static_assert(std::is_base_of<Shape, T>::value, "Template argument must be a Shape");

  TransparentShape2() {}

  template <typename... Args>
  TransparentShape2(const uint8_t transparency_value, Args... args)
      : T(std::forward<Args>(args)...), transparency_value_(transparency_value) {}

  std::string Str() const override {
    std::ostringstream oss;
    oss << T::Str() << " has " << static_cast<float>(transparency_value_) / 255.f * 100.f << "% transparency";
    return oss.str();
  }

 private:
  uint8_t transparency_value_;
};

}  // namespace static_decorator
}  // namespace decorator_pattern
}  // namespace structural

// TEST---------------------------------------------------------------------------------------------------------------|

#include "gtest/gtest.h"

namespace {

using namespace structural::decorator_pattern::static_decorator;

/**
 * Mixing inheritance allows to access the APIs of the decorated objects.
 */

TEST(DecoratorPatternTest, AggregatingManyStaticDecorators) {
  ColoredShape2<Circle> green_circle{"green", 5.f};

  green_circle.Resize(2);

  std::cout << green_circle.Str() << std::endl;
}

TEST(DecoratorPatternTest, AggregatingManyStaticDecoratorsToCreateTransparentShape) {
  ColoredShape2<Circle> green_circle{"green", 5.f};

  green_circle.Resize(2);

  TransparentShape2<ColoredShape2<Square>> square{51, "blue", 10.f};
  std::cout << square.Str() << std::endl;
}

}  // namespace
