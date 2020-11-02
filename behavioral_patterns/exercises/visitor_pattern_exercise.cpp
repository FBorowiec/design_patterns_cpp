/**
 * Implement a double-dispatch visitor called ExpressionPrinter for printing different mathematical expressions. The
 * range of expressions covers addition and multiplication - please put round brackets around addition but not around
 * multiplication! Also, please avoid any blank spaces in output.
 *
 * Example:
 *  - Input: AdditionExpression{Literal{2}, Literal{3}}
 *  - Output: (2+3)
 *
 * Unit test:
 *
 * Value v2{2};
 * Value v3{3};
 * AdditionExpression simple{v2, v3};
 * ExpressionPrinter ep;
 * ep.accept(simple);
 * ASSERT_EQ("(2+3)", ep.str());
 */
#include <sstream>
#include <string>

namespace behavioral {
namespace template_method_exercise {

struct Value;
struct AdditionExpression;
struct MultiplicationExpression;

struct ExpressionVisitor {
  virtual void accept(Value &value) = 0;
  virtual void accept(AdditionExpression &ae) = 0;
  virtual void accept(MultiplicationExpression &me) = 0;
};

struct Expression {
  virtual void visit(ExpressionVisitor &ev) = 0;
};

struct Value : Expression {
  Value(int value) : value_(value) {}

  void visit(ExpressionVisitor &ev) override { ev.accept(*this); }

  int value_;
};

struct AdditionExpression : Expression {
  AdditionExpression(Expression &lhs, Expression &rhs) : lhs_(lhs), rhs_(rhs) {}

  void visit(ExpressionVisitor &ev) override { ev.accept(*this); }

  Expression &lhs_, &rhs_;
};

struct MultiplicationExpression : Expression {
  MultiplicationExpression(Expression &lhs, Expression &rhs) : lhs_(lhs), rhs_(rhs) {}

  void visit(ExpressionVisitor &ev) override { ev.accept(*this); }

  Expression &lhs_, &rhs_;
};

struct ExpressionPrinter : ExpressionVisitor {
  void accept(Value &value) override { oss << value.value_; }

  void accept(AdditionExpression &ae) override {
    oss << "(";
    ae.lhs_.visit(*this);
    oss << "+";
    ae.rhs_.visit(*this);
    oss << ")";
  }

  void accept(MultiplicationExpression &me) override {
    me.lhs_.visit(*this);
    oss << "*";
    me.rhs_.visit(*this);
  }

  std::string str() const { return oss.str(); }

 private:
  std::ostringstream oss;
};

}  // namespace template_method_exercise
}  // namespace behavioral

// TEST---------------------------------------------------------------------------------------------------------------|
#include "gtest/gtest.h"

namespace {

using namespace behavioral::template_method_exercise;

TEST(VisitorPatternExerciseTest, SimpleAddition) {
  Value v{2};
  AdditionExpression simple{v, v};
  ExpressionPrinter ep;
  ep.accept(simple);
  ASSERT_EQ("(2+2)", ep.str());
}

TEST(VisitorPatternExerciseTest, ProductOfAdditionAndValue) {
  Value _2{2};
  Value _3{3};
  Value _4{4};
  AdditionExpression ae{_2, _3};
  MultiplicationExpression expr{ae, _4};
  ExpressionPrinter ep;
  ep.accept(expr);
  ASSERT_EQ("(2+3)*4", ep.str());
}

}  // namespace
