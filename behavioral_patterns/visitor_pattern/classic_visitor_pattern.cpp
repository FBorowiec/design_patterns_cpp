#include <iostream>
#include <sstream>

namespace behavioral {
namespace visitor_pattern {

struct DoubleExpression;
struct AdditionExpression;
struct SubtractionExpression;

struct ExpressionVisitor {
  virtual void Visit(DoubleExpression* de) = 0;
  virtual void Visit(AdditionExpression* ae) = 0;
  virtual void Visit(SubtractionExpression* se) = 0;
};

struct ExpressionPrinter : public ExpressionVisitor {
 public:
  void Visit(DoubleExpression* de) override;
  void Visit(AdditionExpression* ae) override;
  void Visit(SubtractionExpression* se) override;

  std::string str() const { return oss_.str(); }

 private:
  std::ostringstream oss_;
};

struct ExpressionEvaluator : public ExpressionVisitor {
 public:
  void Visit(DoubleExpression* de) override;
  void Visit(AdditionExpression* ae) override;
  void Visit(SubtractionExpression* se) override;

 public:
  double result_;
};

struct Expression {
  virtual void Accept(ExpressionVisitor* visitor) = 0;
  virtual ~Expression() = default;
};

struct DoubleExpression : public Expression {
  explicit DoubleExpression(const double value) : value_(value) {}

  void Accept(ExpressionVisitor* visitor) override { visitor->Visit(this); }

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
  AdditionExpression(Expression* const left, Expression* const right) : left_(left), right_(right) {}
  ~AdditionExpression() {
    delete left_;
    delete right_;
  }

  virtual void Accept(ExpressionVisitor* visitor) { visitor->Visit(this); }

 public:
  Expression* left_;
  Expression* right_;
};

struct SubtractionExpression : public Expression {
  /**
   * 1+2+3
   *    +
   *   / \
   *  1   +
   *     / \
   *    2   3
   */
 public:
  SubtractionExpression(Expression* const left, Expression* const right) : left_(left), right_(right) {}
  ~SubtractionExpression() {
    delete left_;
    delete right_;
  }

  virtual void Accept(ExpressionVisitor* visitor) { visitor->Visit(this); }

 public:
  Expression* left_;
  Expression* right_;
};

void ExpressionPrinter::Visit(DoubleExpression* de) { oss_ << de->value_; }

void ExpressionPrinter::Visit(AdditionExpression* ae) {
  bool need_braces = dynamic_cast<SubtractionExpression*>(ae->right_);
  if (need_braces) oss_ << "(";
  ae->left_->Accept(this);
  oss_ << "+";
  ae->right_->Accept(this);
  if (need_braces) oss_ << ")";
}

void ExpressionPrinter::Visit(SubtractionExpression* se) {
  bool need_braces = dynamic_cast<SubtractionExpression*>(se->right_);
  if (need_braces) oss_ << "(";
  se->left_->Accept(this);
  oss_ << "-";
  se->right_->Accept(this);
  if (need_braces) oss_ << ")";
}

void ExpressionEvaluator::Visit(DoubleExpression* de) { result_ = de->value_; }

void ExpressionEvaluator::Visit(AdditionExpression* ae) {
  ae->left_->Accept(this);
  auto temp = result_;
  ae->right_->Accept(this);
  result_ += temp;
}

void ExpressionEvaluator::Visit(SubtractionExpression* se) {
  se->left_->Accept(this);
  auto temp = result_;
  se->right_->Accept(this);
  result_ = temp - result_;
}

}  // namespace visitor_pattern
}  // namespace behavioral

// TEST---------------------------------------------------------------------------------------------------------------|

#include "gtest/gtest.h"

namespace {

using namespace behavioral::visitor_pattern;

TEST(VisitorPatternTest, UsageOfTheClassicVisitorPattern) {
  auto e =
      new AdditionExpression{new DoubleExpression{1},
                             new SubtractionExpression{new DoubleExpression{2}, new DoubleExpression{3}}};  // 1 + (2-3)

  ExpressionPrinter ep;
  ExpressionEvaluator evaluator;
  ep.Visit(e);
  evaluator.Visit(e);
  std::cout << ep.str() << " = " << evaluator.result_ << std::endl;
}

}  // namespace
