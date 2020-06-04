/**
 * MOTIVATION:
 *  - Object creation logic becomes too convoluted
 *  - Constructor is not descriptive:
 *     & Name mandated by name of containing type
 *     & Cannot overload with same sets of arguments with different names
 *     & Can turn into 'optional parameter hell'
 *  - Object reation (non-peicewise, unlike Builder) can be outsourced to:
 *     & A separate Function (Factory Method)
 *     & That may exist in a separate class (Factory)
 *     & Can Create hierarchy of factories with Abstract Factory
 *
 * DESCRITPION:
 * A component responsible solely for the wholesale (not piecewise) creation of objects.
 * In other words, it's a static method that creates objects.
 * A factory can take care of object creation.
 * A factory can be external or reside inside the object as an inner class.
 * Hierarchies of factories can be used to create related objects.
 */
#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>

namespace creational {
namespace factory_pattern {

enum class PointType { cartesian, polar };

class Point {
 public:
  Point(double x, double y) : x_(x), y_(y) {}

  friend std::ostream& operator<<(std::ostream& os, const Point& point) {
    os << "x: " << point.x_ << " y: " << point.y_;
    return os;
  }

 private:
  double x_, y_;
};

struct PointFactory {
  static Point NewCartesian(double x, double y) { return {x, y}; }

  static Point NewPolar(double rho, double theta) { return {rho * std::cos(theta), rho * std::sin(theta)}; }
};

}  // namespace factory_pattern
}  // namespace creational

// TEST---------------------------------------------------------------------------------------------------------------|

#include "gtest/gtest.h"

namespace {

using namespace creational::factory_pattern;

TEST(FactoryPatternTest, UsageOfTheFactory) {
  auto p = PointFactory::NewPolar(5, M_PI_4);
  std::cout << p << std::endl;
}

}  // namespace
