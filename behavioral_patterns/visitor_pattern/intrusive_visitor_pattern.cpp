/**
 * INTENT:
 * Typically a tool for structure traversal rather than anything else.
 * MOTIVATION:
 * Need to define a new operation on an entire class hierarchy:
 *  - e.g. make a document model printable to HTML/Markdown
 * Do not want to keep modifying every class in the hierarchy (open-close principle and single-responsibility).
 * Need access to the non-common aspects of classes in the hierarchy.
 *  - Cannot put everything into a single interface
 * Create an external component to handle rendering.
 *  - But preferably avoid type checks
 *
 * The Visitor Pattern is when a component (visitor) is allowed to travers the entire inheritance hierarchy.
 * Implemented by propagating a single visit() method throught the entire hierarchy.
 */
#include <iostream>
#include <sstream>

namespace behavioral {
namespace visitor_pattern {

struct Expression {
  virtual ~Expression() = default;
  virtual void Print(std::ostringstream& oss) = 0;
};

struct DoubleExpression : public Expression {
  DoubleExpression(double value) : value_(value) {}
  virtual void Print(std::ostringstream& oss) override { oss << value_; }

 private:
  double value_;
};

struct AdditionExpression : public Expression {
  /**
   * 1+2+3
   *    +
   *   / \
   *  1   +
   *     / \
   *    2   3
   */
 public:
  AdditionExpression(Expression* left, Expression* right) : left_(left), right_(right) {}
  ~AdditionExpression() {
    delete left_;
    delete right_;
  }

  virtual void Print(std::ostringstream& oss) override {
    oss << "(";
    left_->Print(oss);
    oss << "+";
    right_->Print(oss);
    oss << ")";
  }

 private:
  Expression* left_;
  Expression* right_;
};

}  // namespace visitor_pattern
}  // namespace behavioral

// TEST---------------------------------------------------------------------------------------------------------------|

#include "gtest/gtest.h"

namespace {

using namespace behavioral::visitor_pattern;

TEST(VisitorPatternTest, UsageOfTheVisitorPattern) {
  auto e = new AdditionExpression{new DoubleExpression{1},
                                  new AdditionExpression{new DoubleExpression{2}, new DoubleExpression{3}}};

  // how to print (1+(2+3))?
  std::ostringstream oss;
  e->Print(oss);
  std::cout << oss.str() << std::endl;

  delete e;
}

}  // namespace
