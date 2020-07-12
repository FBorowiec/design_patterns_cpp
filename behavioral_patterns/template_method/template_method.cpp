/**
 * INTENT:
 * A high-level blueprint for an algorithm to be completed by inheritors.
 * MOTIVATION:
 * Algorithms can be decomposed into common parts + specifics
 * Strategy pattern does this through composition:
 *  - High-level algorithm uses an interface
 *  - Concrete implementations implement the interface
 * Template method does the same thing through inheritance
 *  - Overall algorithm makes use of abstract member
 *  - Inheritors override the abstract members
 *  - Parent template method invoked
 *
 * Template method allows us to define the 'skeleton' of the algorithm,
 * with concrete implementations defined in subclasses.
 */
#include <iostream>

namespace behavioral {
namespace template_method {

class Game {
 public:
  Game(int number_of_players) : number_of_players_(number_of_players) {}

  void Run() {
    Start();
    while (!HaveWinner()) {
      TakeTurn();
    }
    std::cout << "Player " << GetWinner() << " wins.\n";
  }

 protected:
  int number_of_players_;
  int current_player_{0};
  virtual void Start() = 0;
  virtual bool HaveWinner() = 0;
  virtual void TakeTurn() = 0;
  virtual int GetWinner() = 0;
};

class Chess : public Game {
 public:
  Chess() : Game(2) {}

 protected:
  virtual void Start() { std::cout << "Starting a game of chess with " << number_of_players_ << " players\n"; }

  virtual bool HaveWinner() { return turn_ == max_turns_; }

  virtual void TakeTurn() {
    std::cout << "Turn " << turn_ << " taken by player " << current_player_ << "\n";
    ++turn_;
    current_player_ = (current_player_ + 1) % number_of_players_;
  }

  virtual int GetWinner() { return current_player_; }

 private:
  int turn_{0}, max_turns_{10};
};

}  // namespace template_method
}  // namespace behavioral

// TEST---------------------------------------------------------------------------------------------------------------|

#include "gtest/gtest.h"

namespace {

using namespace behavioral::template_method;

TEST(TemplateMethodTest, UsageOfTheTemplateMethod) {
  Chess chess;
  chess.Run();
}

}  // namespace
