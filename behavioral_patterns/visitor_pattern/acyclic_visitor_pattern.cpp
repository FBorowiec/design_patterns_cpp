/*
 * Cyclic visitor: based on function overloading
 *                 works only on a stable hierarchy
 * Acyclic visitor: based on RTTI
 *                  no hierarchy limitations, but slower
 */
#include <iostream>
#include <sstream>

namespace behavioral {
namespace visitor_pattern {

template <typename Visitable>
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
    using EV = Visitor<Expression>;
    if (auto ev = dynamic_cast<EV*>(&obj)) {
      ev->Visit(*this);
    }
  }
};

struct DoubleExpression : public Expression {
 public:
  DoubleExpression(double value) : value_(value) {}

  virtual void Accept(VisitorBase& obj) {
    using DEV = Visitor<DoubleExpression>;
    if (auto ev = dynamic_cast<DEV*>(&obj)) {
      ev->Visit(*this);
    }
  }

 public:
  double value_;
};

struct AdditionExpression : public Expression {
 public:
  AdditionExpression(Expression* const left, Expression* const right) : left_(left), right_(right) {}
  ~AdditionExpression() {
    delete left_;
    delete right_;
  }

  virtual void Accept(VisitorBase& obj) {
    using AEV = Visitor<AdditionExpression>;
    if (auto ev = dynamic_cast<AEV*>(&obj)) {
      ev->Visit(*this);
    }
  }

 public:
  Expression* left_;
  Expression* right_;
};

struct ExpressionPrinter : public VisitorBase, Visitor<DoubleExpression>, Visitor<AdditionExpression> {
 public:
  void Visit(AdditionExpression& obj) override {
    oss_ << "(";
    obj.left_->Accept(*this);
    oss_ << "+";
    obj.right_->Accept(*this);
    oss_ << ")";
  }

  void Visit(DoubleExpression& obj) override { oss_ << obj.value_; }

  std::string str() { return oss_.str(); }

 private:
  std::ostringstream oss_;
};

}  // namespace visitor_pattern
}  // namespace behavioral

// TEST---------------------------------------------------------------------------------------------------------------|

#include "gtest/gtest.h"

namespace {

using namespace behavioral::visitor_pattern;

TEST(VisitorPatternTest, UsageOfTheAcyclicVisitorPattern) {
  auto e = new AdditionExpression{new DoubleExpression{1},
                                  new AdditionExpression{new DoubleExpression{2}, new DoubleExpression{3}}};

  ExpressionPrinter ep;
  ep.Visit(*e);

  std::cout << ep.str() << std::endl;
}

}  // namespace
