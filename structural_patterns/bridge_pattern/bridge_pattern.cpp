/**
 * Connecting components together through abstractions.
 * MOTIVATION:
 * A Bridge prevents a 'Cartesian product' complexity explosion
 * Example:
 *  - Base class ThreadSchefuler
 *  - Can be preemptive or cooperative
 *  - Can run on Windows or Unix
 *  - End up with 2x2 scenario: WindowsPTS, UnitPTS, WindotwsCTS, UnixCTS
 * The Bridge pattern avoids the entity explosion.
 * It is a mechanism that decouples an interface (hierarchy) from an implementation (hierarchy).
 * It's essentialy a stronger form of encapsulation.
 */
#include <iostream>
#include <string>

namespace structural {
namespace bridge_pattern {

/**
 * Given:
 *  Shapes: circle / square
 *  Renderer: raster / vector
 *
 * In order to avoid a 2x2 situation:
 *  RasterCircleRenderer
 *  RasterSquareRenderer
 *  VectorCircleRenderer
 *  VectorSquareRenderer
 *
 * This grows much more if you add more categories.
 * But using the bridge pattern this can be avoided.
 */

struct Renderer {
  virtual void RenderCircle(float x, float y, float radius) = 0;
};

struct RasterRenderer : public Renderer {
  virtual void RenderCircle(float x, float y, float radius) override {
    std::cout << "Rasterizing a (" << x << ", " << y << ") circle of radius " << radius << std::endl;
  }
};

struct VectorRenderer : public Renderer {
  virtual void RenderCircle(float x, float y, float radius) override {
    std::cout << "Drawing a vector (" << x << ", " << y << ") circle of radius " << radius << std::endl;
  }
};

struct Shape {
 protected:
  Shape(Renderer& renderer) : renderer_bridge(renderer) {}

  // Bridge
  Renderer& renderer_bridge;

 public:
  virtual void Draw() = 0;
  virtual void Resize(float factor) = 0;
};

struct Circle : public Shape {
 public:
  Circle(Renderer& renderer, float x, float y, float radius) : Shape(renderer), x_(x), y_(y), radius_(radius) {}

  void Draw() override { renderer_bridge.RenderCircle(x_, y_, radius_); }

  void Resize(float factor) override { radius_ *= factor; }

 private:
  float x_, y_, radius_;
};

}  // namespace bridge_pattern
}  // namespace structural

// TEST---------------------------------------------------------------------------------------------------------------|

#include "gtest/gtest.h"

namespace {

using namespace structural::bridge_pattern;

TEST(BridgePatternTest, UsageOfTheBridgePattern) {
  // Bridge
  RasterRenderer rr;

  Circle raster_circle(rr, 5, 5, 5);
  raster_circle.Draw();
  raster_circle.Resize(2);
  raster_circle.Draw();
}

}  // namespace
