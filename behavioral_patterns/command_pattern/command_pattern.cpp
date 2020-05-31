/**
 * INTENT:
 * Avoid coupling the sender of a request to its receiver by giving more than one object a chance to handle ther
 * request. Chain the receiving objects and pass the request along the chain until an object handles it.
 * MOTIVATION:
 *  - Ordinary C++ statements are perishable
 *  - Want an object that represents an operation
 *
 * It is an object that represents an instruction to perform a particular action. Conatins all the information
 * necessary for the action to be taken.
 *
 * Command / Query separation:
 * Command = asking for an action or change (e.g., please set your attack value to 2)
 * Query = asking for information (e.g., please give me your attack value)
 * CQS = having separate means of sending commands and queries
 * In GoF context, bot hcommands and queries are represented with the Command design pattern.
 */
#include <iostream>
#include <ostream>
#include <vector>

namespace behavioral {
namespace command_pattern {

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

}  // namespace command_pattern
}  // namespace behavioral

// TEST---------------------------------------------------------------------------------------------------------------|

#include "gtest/gtest.h"

namespace {

using namespace behavioral::command_pattern;

TEST(CommandTest, UsageOfTheCommandPatternForDepositingMoney) {
  BankAccount ba;
  std::vector<BankAccountCommand> commands{BankAccountCommand{BankAccountCommand::deposit, ba, 100},
                                           BankAccountCommand{BankAccountCommand::withdraw, ba, 20}};

  std::cout << ba;

  for (auto& cmd : commands) {
    cmd.Call();
  }

  std::cout << ba;
}

TEST(CommandTest, UsageOfTheCommandPatternForUndoingAMoneyDeposit) {
  BankAccount ba;
  std::vector<BankAccountCommand> commands{BankAccountCommand{BankAccountCommand::deposit, ba, 100},
                                           BankAccountCommand{BankAccountCommand::withdraw, ba, 20}};

  std::cout << ba;

  for (auto& cmd : commands) {
    cmd.Call();
  }

  // Undo
  for (auto it = commands.rbegin(); it != commands.rend(); ++it) {
    it->Undo();
  }

  std::cout << ba;
}

}  // namespace
