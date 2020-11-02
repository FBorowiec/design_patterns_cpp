/**
 * A TokenMachine is in charge of keeping tokes.
 * Each Token is reference type with a single numberical value.
 * The machine supports adding tokens and, when it does,
 * it returns a memento representing the state of that system at that given time.
 * Implement the Memento design pattern for this scenario. Pay close attention to the situation where a token is fed in
 * as a smart pointer and its value is subsequently changed on that pointer - you still need to return the correct
 * system snapshot!
 */
#include <memory>
#include <vector>

namespace behavioral {
namespace memento_pattern_exercise {

struct Token {
  Token(int value) : value_(value) {}

  int value_;
};

struct Memento {
  std::vector<std::shared_ptr<Token>> tokens;
};

struct TokenMachine {
  std::vector<std::shared_ptr<Token>> tokens;

  Memento add_token(int value) { return add_token(std::make_shared<Token>(value)); }

  // adds the token to the set of tokens and returns the
  // snapshot of the entire system
  Memento add_token(const std::shared_ptr<Token>& token) {
    tokens.push_back(token);
    Memento m;
    for (auto t : tokens) m.tokens.emplace_back(std::make_shared<Token>(t->value_));
    return m;
  }

  // reverts the system to a state represented by the token
  void revert(const Memento& m) {
    tokens.clear();
    for (auto t : m.tokens) tokens.emplace_back(std::make_shared<Token>(t->value_));
  }
};

}  // namespace memento_pattern_exercise
}  // namespace behavioral

// TEST---------------------------------------------------------------------------------------------------------------|
#include <iostream>
#include "gtest/gtest.h"

namespace {

using namespace behavioral::memento_pattern_exercise;

TEST(MementoPatternExerciseTest, SingleTokenTest) {
  TokenMachine tm;
  auto m = tm.add_token(123);
  tm.add_token(456);
  tm.revert(m);
  ASSERT_EQ(1, tm.tokens.size());
  ASSERT_EQ(123, tm.tokens[0]->value_);
}

TEST(MementoPatternExerciseTest, TwoTokenTest) {
  TokenMachine tm;
  tm.add_token(1);
  auto m = tm.add_token(2);
  tm.add_token(3);
  tm.revert(m);
  ASSERT_EQ(2, tm.tokens.size());
  ASSERT_EQ(1, tm.tokens[0]->value_) << "First toke should have value 1, you got " << tm.tokens[0]->value_;
  ASSERT_EQ(2, tm.tokens[1]->value_);
}

TEST(MementoPatternExerciseTest, FiddledTokenTest) {
  TokenMachine tm;
  std::cout << "Made a token with value=111 and kept a reference\n";
  auto token = std::make_shared<Token>(111);
  std::cout << "Added this token to the list\n";
  tm.add_token(token);
  auto m = tm.add_token(222);
  std::cout << "Changed this token's value to 333 :)\n";
  token->value_ = 333;
  tm.revert(m);

  ASSERT_EQ(2, tm.tokens.size()) << "At this point, token machine should have exactly "
                                 << "two tokens, you got " << tm.tokens.size();

  ASSERT_EQ(111, tm.tokens[0]->value_) << "You got the token value wrong here. "
                                       << "Hint: did you init the memento by-value?";
}

}  // namespace
