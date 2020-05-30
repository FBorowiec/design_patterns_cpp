/**
 * Subtypes should be immediately substitutable for their base types.
 * "If it looks like a duck and quacks like a duck but needs batteries, you probably have a wrong abstraction"
 */
#include <iostream>

namespace solid_principles {
namespace liskov_substitution_principle {

class Rectangle {
 public:
  Rectangle(int width, int height) : width_(width), height_(height) {}
  int GetWidth() { return width_; }
  int GetHeight() { return height_; }
  virtual void SetWidth(int width) { Rectangle::width_ = width; }
  virtual void SetHeight(int height) { Rectangle::height_ = height; }

  int Area() const { return width_ * height_; }

 protected:
  int width_{}, height_{};
};

static void Process(Rectangle& r) {
  int w = r.GetWidth();
  r.SetHeight(10);

  std::cout << "expected area = " << w * 10 << ", got area = " << r.Area() << std::endl;
}

namespace bad {
/**
 * BAD! We've just violated the Liskov Substitution Principle.
 * Any derived class should be substitutable into the "Process(Rectangle& r)" function.
 * For the square the center mechanic is broken. Setting Height also sets width and vice versa.
 */
class Square : public Rectangle {
 public:
  Square(int size) : Rectangle(size, size) {}
  void SetWidth(int width) override { this->width_ = this->height_ = width; }
  void SetHeight(int height) override { this->height_ = this->width_ = height; }
};
}  // namespace bad

namespace good {
/**
 * The very idea of inheriting square from rectangle is not the best idea.
 * One solution might be modyfying the rectangle adding a boolean flag to check whetether it's a square or not.
 * Another might be creating a factory:
 */
struct RectangleFactory {
  static Rectangle CreateRectangle(int w, int h) { return Rectangle(w, h); }
  static Rectangle CreateSquare(int size) { return Rectangle(size, size); }
};
}  // namespace good

}  // namespace liskov_substitution_principle
}  // namespace solid_principles

// TEST---------------------------------------------------------------------------------------------------------------|

#include "gtest/gtest.h"

namespace {

using namespace solid_principles::liskov_substitution_principle;

TEST(LiskovSubstitutionPrincipleTest, ViolationOfTheLiskovSubstitutionPrinciple) {
  Rectangle r{3, 4};
  Process(r);

  bad::Square sq{5};
  Process(sq);
}

TEST(LiskovSubstitutionPrincipleTest, ProperFollowingOfTheLiskovSubstitutionPrinciple) {
  Rectangle r{3, 4};
  Process(r);

  auto sq = good::RectangleFactory::CreateSquare(5);
  Process(sq);
}

}  // namespace
