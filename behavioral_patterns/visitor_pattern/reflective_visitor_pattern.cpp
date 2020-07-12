#include <iostream>
#include <sstream>

namespace behavioral {
namespace visitor_pattern {

struct Expression {
  virtual ~Expression() = default;
  // Not needed anymore - preserving the open-close principle
  // virtual void Print(std::ostringstream& oss) = 0;
};

struct DoubleExpression : public Expression {
  DoubleExpression(double value) : value_(value) {}
  /*  // Not needed anymore - preserving the open-close principle
  virtual void Print(std::ostringstream& oss) override { oss << value_; }
  */

 public:
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

  /*  // Not needed anymore - preserving the open-close principle
  virtual void Print(std::ostringstream& oss) override {
    oss << "(";
    left_->Print(oss);
    oss << "+";
    right_->Print(oss);
    oss << ")";
  }
  */

 public:
  Expression* left_;
  Expression* right_;
};

struct ExpressionPrinter {
 public:
  void Print(Expression* e) {
    if (auto de = dynamic_cast<DoubleExpression*>(e)) {
      oss_ << de->value_;
    } else if (auto ae = dynamic_cast<AdditionExpression*>(e)) {
      oss_ << "(";
      Print(ae->left_);
      oss_ << "+";
      Print(ae->right_);
      oss_ << ")";
    }
  }

  std::string str() const { return oss_.str(); }

 private:
  std::ostringstream oss_;
};

}  // namespace visitor_pattern
}  // namespace behavioral

// TEST---------------------------------------------------------------------------------------------------------------|

#include "gtest/gtest.h"

namespace {

using namespace behavioral::visitor_pattern;

TEST(VisitorPatternTest, UsageOfTheReflectiveVisitorPattern) {
  auto e = new AdditionExpression{new DoubleExpression{1},
                                  new AdditionExpression{new DoubleExpression{2}, new DoubleExpression{3}}};

  ExpressionPrinter ep;
  ep.Print(e);
  std::cout << ep.str() << std::endl;
}

}  // namespace
