/**
 * INTENT:
 * Keep a memento of an object's state to return to that state.
 * MOTIVATION:
 * An object or system goes through changes:
 *  - e.g., a bank account gets depostis and withdrawals.
 * There are different wyas of navigating those changes.
 * One way is to record every change (Command pattern) and teach a command to 'undo' itself.
 * Another is to simply save snapshots of the system (Memento pattern).
 *
 * Memento is a toke/handle representing the system state.
 * Lets us roll back to the state when the token was generated.
 * May or may not directly expose state information.
 */
#include <iostream>
#include <memory>
#include <vector>

namespace behavioral {
namespace memento_pattern {

class Memento {
 public:
  Memento(int balance) : balance_(balance) {}

  friend class BankAccount2;

 private:
  int balance_;
};

class BankAccount2 {
 public:
  BankAccount2(int balance) : balance_(balance) {}

  std::shared_ptr<Memento> Deposit(int amount) {
    balance_ += amount;
    auto m = std::make_shared<Memento>(balance_);
    changes_.push_back(m);
    ++current_;
    return m;
  }

  void Restore(const std::shared_ptr<Memento>& m) {
    if (m) {
      balance_ = m->balance_;
      changes_.push_back(m);
      current_ = static_cast<int>(changes_.size()) - 1;
    }
  }

  std::shared_ptr<Memento> Undo() {
    if (current_ > 0) {
      --current_;
      auto m = changes_[static_cast<long unsigned int>(current_)];
      balance_ = m->balance_;
      return m;
    }
    return {};
  }

  std::shared_ptr<Memento> Redo() {
    if (current_ + 1 < static_cast<int>(changes_.size())) {
      ++current_;
      auto m = changes_[static_cast<long unsigned int>(current_)];
      balance_ = m->balance_;
      return m;
    }
    return {};
  }

  friend std::ostream& operator<<(std::ostream& os, const BankAccount2& ba) {
    os << "Balance: " << ba.balance_;
    return os;
  }

 private:
  int balance_{0};
  std::vector<std::shared_ptr<Memento>> changes_;
  int current_{0};
};

}  // namespace memento_pattern
}  // namespace behavioral

// TEST---------------------------------------------------------------------------------------------------------------|

#include "gtest/gtest.h"

namespace {

using namespace behavioral::memento_pattern;

TEST(MementoPatternTest, UsageOfTheMementoPattern) {
  BankAccount2 ba{100};
  ba.Deposit(50);  // 150
  ba.Deposit(25);  // 175
  std::cout << ba << std::endl;

  ba.Undo();
  std::cout << "Undo 1: " << ba << std::endl;
  ba.Undo();
  std::cout << "Undo 2: " << ba << std::endl;
  ba.Redo();
  std::cout << "Redo: " << ba << std::endl;
}

}  // namespace
