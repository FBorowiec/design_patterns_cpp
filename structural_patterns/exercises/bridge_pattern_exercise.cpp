/**
 * You are given an example of an inheritance hierarchy which results in Cartesian-product duplication.
 * Please refactor this hierarchy, giving the base class Shape an initializer that takes a Renderer
 * as well as VectorRenderer and RasterRenderer:
 *
 * struct Shape {
 *   std::string name;
 * };
 *
 * struct Triangle : public Shape {
 *   Triangle() { name = "Triangle"; }
 * };
 *
 * struct Square : public Shape {
 *   Square() { name = "Square"; }
 * };
 *
 * struct VectorSquare : public Square {
 *   std::string str() const { return "Drawing " + name + " as lines"; }
 * };
 *
 * struct RasterSquare : public Square {
 *   std::string str() const { return "Drawing " + name + " as pixels"; }
 * };
 *
 * The expectation is that each constructed object has a member called str() that returns its textual
 * representation, for example:
 * Triangle(RasterRenderer()).str()  // returns "Drawing a Triangle as pixels"
 */
#include <sstream>
#include <string>

namespace structural {
namespace bridge_pattern_exercise {

struct Renderer {
  virtual std::string what_to_render_as() const = 0;
};

struct Shape {
  Shape(const Renderer& renderer) : renderer_{renderer} {}

  std::string str() const {
    std::ostringstream oss;
    oss << "Drawing " << name_ << " as " << renderer_.what_to_render_as();
    return oss.str();
  }

  std::string name_;
  const Renderer& renderer_;
};

struct Triangle : Shape {
  explicit Triangle(const Renderer& renderer) : Shape{renderer} { name_ = "Triangle"; }
};

struct Square : Shape {
  explicit Square(const Renderer& renderer) : Shape{renderer} { name_ = "Square"; }
};

struct RasterRenderer : Renderer {
  std::string what_to_render_as() const override { return "pixels"; }
};

struct VectorRenderer : Renderer {
  std::string what_to_render_as() const override { return "lines"; }
};

}  // namespace bridge_pattern_exercise
}  // namespace structural

// TEST---------------------------------------------------------------------------------------------------------------|
#include "gtest/gtest.h"

namespace {

using namespace structural::bridge_pattern_exercise;

TEST(BridgePatternExerciseTest, SimpleTest) { ASSERT_EQ("Drawing Square as lines", Square{VectorRenderer{}}.str()); }

}  // namespace
