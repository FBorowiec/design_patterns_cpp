/**
 * You are asked to write an expression processor for simple numberic expressions with the following constraints:
 *  - Expressions use integral values (e.g., "13"),
 *    single-letter variables defined in variables, as well as + and - operators only
 *  - There is no need to support braces or any other operations
 *  - If a variable is not found in Variables (or if we encounter a variable with >1 letter, e.g. ab),
 *    the evaluator returns 0 (zero)
 *  - In case of any parsing failure, evaluator returns 0
 *
 * Examples:
 *  - calculate("1+2+3") should return 6
 *  - calculate("1+2+xy") should return 0
 *  - calculate("10-2-x") when x=3 is in variables should return 5
 */
#include <iostream>
#include <regex>
#include <string>
#include <unordered_map>
#include <vector>

namespace behavioral {
namespace interpreter_pattern_exercise {

inline std::vector<std::string> split(const std::string& stringToSplit) {
  std::vector<std::string> result;
  size_t pos = 0, lastPos = 0;
  while ((pos = stringToSplit.find_first_of("+-", lastPos)) != std::string::npos) {
    result.push_back(stringToSplit.substr(lastPos, pos - lastPos + 1));
    lastPos = pos + 1;
  }
  result.push_back(stringToSplit.substr(lastPos));
  return result;
}

struct ExpressionProcessor {
  std::unordered_map<char, int> variables;

  enum NextOp { nothing, plus, minus };

  int calculate(const std::string& expression) {
    int current;
    auto next_op = nothing;
    auto parts = split(expression);

    std::cout << "parts (" << parts.size() << "): ";
    for (auto& part : parts) std::cout << "`" << part << "` ";
    std::cout << std::endl;

    for (auto& part : parts) {
      auto no_op = split(part);
      auto first = no_op[0];
      int value;

      try {
        value = std::stoi(first);
      } catch (const std::invalid_argument&) {
        if (first.length() == 1 && variables.find(first[0]) != variables.end()) {
          value = variables[first[0]];
        } else
          return 0;
      }

      switch (next_op) {
        case nothing:
          current = value;
          break;
        case plus:
          current += value;
          break;
        case minus:
          current -= value;
          break;
        default:
          break;
      }

      if (*part.rbegin() == '+')
        next_op = plus;
      else if (*part.rbegin() == '-')
        next_op = minus;
    }

    return current;
  }
};

}  // namespace interpreter_pattern_exercise
}  // namespace behavioral

// TEST---------------------------------------------------------------------------------------------------------------|
#include "gtest/gtest.h"

namespace {

using namespace behavioral::interpreter_pattern_exercise;

TEST(InterpreterPatternExerciseTest, SimpleTest) {
  ExpressionProcessor ep;
  ep.variables['x'] = 5;

  ASSERT_EQ(1, ep.calculate("1"));
  ASSERT_EQ(3, ep.calculate("1+2"));
  ASSERT_EQ(6, ep.calculate("1+x"));
  ASSERT_EQ(0, ep.calculate("1+xy"));
}

}  // namespace
