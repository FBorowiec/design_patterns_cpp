/**
 * A virtual proxy gives the apperance of working with the actual object
 * even though it might not have been created.
 */
#include <iostream>
#include <memory>

namespace structural {
namespace proxy_pattern {

struct Image {
  virtual void Draw() = 0;
};

struct Bitmap : public Image {
  Bitmap(const std::string& filename) { std::cout << "Loading bitmap from " << filename << std::endl; }

  void Draw() override { std::cout << "Drawing bitmap" << std::endl; }
};

// Virtual Proxy
struct LazyBitmap : public Image {
  LazyBitmap(const std::string& filename) : filename_(filename) {}

  void Draw() override {
    if (!bmp) bmp = std::make_unique<Bitmap>(filename_);
    bmp->Draw();
  }

 private:
  std::string filename_;
  std::unique_ptr<Bitmap> bmp{nullptr};
};

}  // namespace proxy_pattern
}  // namespace structural

// TEST---------------------------------------------------------------------------------------------------------------|

#include "gtest/gtest.h"

namespace {

using namespace structural::proxy_pattern;

TEST(VirtualProxyPatternTest, NoUsageOfTheVirtualProxyPattern) {
  // Rendering is not performed in proper order!
  Bitmap bmp{"pokemon.png"};
  bmp.Draw();
}

TEST(VirtualProxyPatternTest, ProperUsageOfTheVirtualProxyPattern) {
  // Now it is!
  LazyBitmap bmp{"pokemon.png"};
  bmp.Draw();
}

}  // namespace
