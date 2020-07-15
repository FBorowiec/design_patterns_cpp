#include <iostream>
#include <sstream>

namespace behavioral {
namespace visitor_pattern {

template <typename visitable>
struct Visitor {
 public:
  virtual void Visit(Visitable& obj) = 0;
};

struct VisitorBase {
 public:
  virtual ~VisitorBase() = default;
};

struct Expression {
  virtual ~Expression() = default;

  virtual void Accept(VisitorBase& obj) {

  }
};

}  // namespace visitor_pattern
}  // namespace behavioral

// TEST---------------------------------------------------------------------------------------------------------------|

#include "gtest/gtest.h"

namespace {

using namespace behavioral::visitor_pattern;

TEST(VisitorPatternTest, UsageOfTheAcyclicVisitorPattern) {
}

}  // namespace
