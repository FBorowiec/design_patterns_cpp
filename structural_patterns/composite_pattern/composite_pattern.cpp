/**
 * Treating individual and aggregate objects uniformly.
 * MOTIVATION:
 * Objects use other objects' fileds/properties/members through inheritance and composition.
 * Composition lets us make compound objects:
 *  - e.g, a mathematical expression composed of simple expressions
 *  - a grouping of shapes that consists of several shapes
 * Composite desing pattern is used to treat both single (scalar) and composite objects uniformly:
 *  - i.e. Foo and Collection<Foo> have common APIs
 */
#include <iostream>
#include <string>
#include <vector>

namespace structural {
namespace composite_pattern {

// Composite
struct GraphicObject {
  virtual void Draw() = 0;
};

struct Circle : public GraphicObject {
  void Draw() override { std::cout << "Circle" << std::endl; }
};

struct Group : GraphicObject {
  Group(std::string name) : name_(name) {}

  void Draw() override {
    std::cout << "Group " << name_ << " contains: " << std::endl;
    for (auto&& o : objects) o->Draw();
  }

  std::string name_;
  std::vector<GraphicObject*> objects;
};

}  // namespace composite_pattern
}  // namespace structural

// TEST---------------------------------------------------------------------------------------------------------------|

#include "gtest/gtest.h"

namespace {

using namespace structural::composite_pattern;

TEST(CompositePatternTest, UsageOfTheCompositePattern) {
  Group root("root");
  Circle c1, c2;
  root.objects.push_back(&c1);

  Group subgroup("sub");
  subgroup.objects.push_back(&c2);
  root.objects.push_back(&subgroup);

  root.Draw();
}

}  // namespace
