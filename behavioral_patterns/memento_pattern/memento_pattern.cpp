/**
 * INTENT:
 * Keep a memento of an object's state to return to that state.
 *
 * MOTIVATION:
 *  - Mementos are used to roll back states arbitrarily
 *  - A memento is simply a token/handle class with (typically) no functions of its own.
 *  - A memento is not required to expose directly the state(s) to which it reverts the system.
 *  - Can be used to implement undo/redo.
 *
 * An object or system goes through changes:
 *  - e.g., a bank account gets deposits and withdrawals.
 * There are different ways of navigating those changes.
 * One way is to record every change (Command pattern) and teach a command to 'undo' itself.
 * Another is to simply save snapshots of the system (Memento pattern).
 *
 * Memento is a token/handle representing the system state.
 * Lets us roll back to the state when the token was generated.
 * May or may not directly expose state information.
 */
#include <iostream>

namespace behavioral {
namespace memento_pattern {

class Memento {
 public:
  Memento(int balance) : balance_(balance) {}

  friend class BankAccount;

 private:
  int balance_{0};
};

class BankAccount {
 public:
  BankAccount(int balance) : balance_(balance) {}

  Memento Deposit(int amount) {
    balance_ += amount;
    return Memento{balance_};
  }

  void Restore(const Memento& m) { balance_ = m.balance_; }

  friend std::ostream& operator<<(std::ostream& os, const BankAccount& account) {
    os << "Balance: " << account.balance_;
    return os;
  }

 private:
  int balance_{0};
};

}  // namespace memento_pattern
}  // namespace behavioral

// TEST---------------------------------------------------------------------------------------------------------------|

#include "gtest/gtest.h"

namespace {

using namespace behavioral::memento_pattern;

TEST(MementoPatternTest, UsageOfTheMementoPattern) {
  BankAccount ba{100};
  auto m1 = ba.Deposit(50);  // 150
  auto m2 = ba.Deposit(25);  // 175

  std::cout << ba << "\n";

  ba.Restore(m1);
  std::cout << "Back to m1: " << ba << "\n";

  ba.Restore(m2);
  std::cout << "Back to m2: " << ba << "\n";
}

}  // namespace
