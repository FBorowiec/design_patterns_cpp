#include <iostream>
#include <ostream>
#include <vector>

namespace behavioral {
namespace composite_command_pattern {

struct BankAccount {
 public:
  void Deposit(int amount) {
    balance += amount;
    std::cout << "Deposited: " << amount << ", balance is now: " << balance << std::endl;
  }

  bool Withdraw(int amount) {
    if (balance - amount >= overdraft_limit) {
      balance -= amount;
      std::cout << "Withdrew: " << amount << ", balance is now: " << balance << std::endl;
      return 1;
    }
    return 0;
  }

  friend std::ostream& operator<<(std::ostream& os, const BankAccount& ba) {
    return os << "Current balance: " << ba.balance << std::endl;
  }

 private:
  int balance{0};
  int overdraft_limit{-500};
};

struct Command {
  virtual void Call() = 0;
  virtual void Undo() = 0;

  bool succeeded = false;
};

struct BankAccountCommand : public Command {
  enum Action { deposit, withdraw } action_;
  BankAccountCommand(Action action, BankAccount& account, int amount)
      : action_(action), account_(account), amount_(amount) {
    succeeded = false;
  }

  void Call() override {
    switch (action_) {
      case deposit:
        account_.Deposit(amount_);
        succeeded = true;
        break;
      case withdraw:
        succeeded = account_.Withdraw(amount_);
        break;
      default:
        break;
    }
  }

  void Undo() override {
    if (!succeeded) return;
    switch (action_) {
      case deposit:
        succeeded = account_.Withdraw(amount_);
        break;
      case withdraw:
        account_.Deposit(amount_);
        succeeded = true;
        break;
      default:
        break;
    }
  }

 private:
  BankAccount& account_;
  int amount_{0};
};

struct CompositeBanckAccountCommand : public Command {
  CompositeBanckAccountCommand(const std::vector<BankAccountCommand>& items) : items_(items) {}

  void Call() override {
    bool ok = true;
    for (auto& cmd : items_) {
      if (ok) {
        cmd.Call();
        ok = cmd.succeeded;
      } else {
        cmd.succeeded = false;
      }
    }
  }

  void Undo() override {
    for (auto it = items_.rbegin(); it != items_.rend(); ++it) {
      it->Undo();
    }
  }

 private:
  std::vector<BankAccountCommand> items_{};
};

struct MoneyTransferCommand : public CompositeBanckAccountCommand {
 public:
  MoneyTransferCommand(BankAccount& from, BankAccount& to, int amount)
      : CompositeBanckAccountCommand({BankAccountCommand{BankAccountCommand::withdraw, from, amount},
                                      BankAccountCommand{BankAccountCommand::deposit, to, amount}}) {}
};

}  // namespace composite_command_pattern
}  // namespace behavioral

// TEST---------------------------------------------------------------------------------------------------------------|

#include "gtest/gtest.h"

namespace {

using namespace behavioral::composite_command_pattern;

TEST(CommandTest, UsageOfTheCommandPatternForDepositingMoney) {
  BankAccount ba, ba2;
  ba.Deposit(100);

  MoneyTransferCommand cmd{ba, ba2, 50};

  cmd.Call();
  std::cout << ba << std::endl << ba2 << std::endl;

  cmd.Undo();
  std::cout << ba << std::endl << ba2 << std::endl;
}

TEST(CommandTest, UsageOfTheSuccessFlagForIllegalOperations) {
  BankAccount ba, ba2;
  ba.Deposit(100);

  MoneyTransferCommand cmd{ba, ba2, 5000};

  cmd.Call();
  std::cout << ba << std::endl << ba2 << std::endl;

  cmd.Undo();
  std::cout << ba << std::endl << ba2 << std::endl;
}

}  // namespace
