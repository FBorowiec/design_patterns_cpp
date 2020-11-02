/**
 * Consider the quadratic equation and its canonical solution:
 * a*x^2 + b*x + c = 0
 * x = (-b +- sqrt(b^2 - 4*a*c)) / (2*a)
 *
 * The part "b^2 - 4*a*c" is called the discriminant.
 * Suppose we want to provide and API with two different strategies for calculating the discriminant:
 * 1. In OrdinaryDiscriminantStrategy, if the discriminant is negative, we return it as-is. This is OK, since our main
 * API returns std::complex numbers anyway.
 * 2. In RealDiscriminantStrategy, if the discriminant is negative, the return value is NaN (Not a Number). NaN
 * propagates throughout the calculation, so the equation solver gives two NaN values.
 *
 * Please implement both of these strategies as well as the equation solver itself. With regards to plus-minus in the
 * formula, please return the + result as the first element and - as the second.
 */
#include <cmath>
#include <complex>
#include <iostream>
#include <tuple>
#include <vector>

namespace behavioral {
namespace strategy_pattern_exercise {

struct DiscriminantStrategy {
  virtual double CalculateDiscriminant(double a, double b, double c) = 0;
};

struct OrdinaryDiscriminantStrategy : DiscriminantStrategy {
  double CalculateDiscriminant(double a, double b, double c) override { return std::pow(b, 2) - 4 * a * c; }
};

struct RealDiscriminantStrategy : DiscriminantStrategy {
  double CalculateDiscriminant(double a, double b, double c) override {
    auto discriminant = std::pow(b, 2) - 4 * a * c;
    return discriminant >= 0 ? discriminant : std::nan("1");
  }
};

class QuadraticEquationSolver {
 public:
  QuadraticEquationSolver(DiscriminantStrategy& strategy) : strategy_(strategy) {}

  std::tuple<std::complex<double>, std::complex<double>> Solve(double a, double b, double c) {
    std::complex<double> discriminant{strategy_.CalculateDiscriminant(a, b, c), 0};
    auto root_disc = sqrt(discriminant);
    return {(-b + root_disc) / (2 * a), (-b - root_disc) / (2 * a)};
  }

 private:
  DiscriminantStrategy& strategy_;
};

}  // namespace strategy_pattern_exercise
}  // namespace behavioral

// TEST---------------------------------------------------------------------------------------------------------------|
#include "gtest/gtest.h"

namespace {

using namespace behavioral::strategy_pattern_exercise;

TEST(StrategyPatternExerciseTest, PositiveTestOrdinaryStrategy) {
  OrdinaryDiscriminantStrategy strategy;
  QuadraticEquationSolver solver{strategy};
  auto results = solver.Solve(1, 10, 16);
  ASSERT_EQ(std::complex<double>(-2, 0), std::get<0>(results));
  ASSERT_EQ(std::complex<double>(-8, 0), std::get<1>(results));
}

TEST(StrategyPatternExerciseTest, PositiveTestRealStrategy) {
  RealDiscriminantStrategy strategy;
  QuadraticEquationSolver solver{strategy};
  auto results = solver.Solve(1, 10, 16);
  ASSERT_EQ(std::complex<double>(-2, 0), std::get<0>(results));
  ASSERT_EQ(std::complex<double>(-8, 0), std::get<1>(results));
}

TEST(StrategyPatternExerciseTest, NegativeTestOrdinaryStrategy) {
  OrdinaryDiscriminantStrategy strategy;
  QuadraticEquationSolver solver{strategy};
  auto results = solver.Solve(1, 4, 5);
  ASSERT_EQ(std::complex<double>(-2, 1), std::get<0>(results));
  ASSERT_EQ(std::complex<double>(-2, -1), std::get<1>(results));
}

TEST(StrategyPatternExerciseTest, NegativeTestRealStrategy) {
  RealDiscriminantStrategy strategy;
  QuadraticEquationSolver solver{strategy};
  auto results = solver.Solve(1, 4, 5);
  auto x1 = std::get<0>(results);
  auto x2 = std::get<1>(results);
  EXPECT_TRUE(std::isnan(x1.real()));
  EXPECT_TRUE(std::isnan(x2.real()));
  EXPECT_TRUE(std::isnan(x1.imag()));
  EXPECT_TRUE(std::isnan(x2.imag()));
}

}  // namespace
