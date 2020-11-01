/**
 * Implement the Account::proxess() function to process different account commands. The rules are  obvious:
 *  - Success indicates whether the operation was successful
 *  - You can only withdraw money if you have enough in your account
 */
namespace behavioral {
namespace command_pattern_exercise {

struct Command {
  enum Action { deposit, withdraw } action;
  int amount{0};
  bool success{false};
};

struct Account {
  int balance{0};

  void process(Command& cmd) {
    switch (cmd.action) {
      case Command::deposit:
        balance += cmd.amount;
        cmd.success = true;
        break;
      case Command::withdraw:
        cmd.success = (balance >= cmd.amount);
        if (cmd.success) balance -= cmd.amount;
        break;
      default:
        cmd.success = false;
    }
  }
};

}  // namespace command_pattern_exercise
}  // namespace behavioral

// TEST---------------------------------------------------------------------------------------------------------------|
#include "gtest/gtest.h"

namespace {

using namespace behavioral::command_pattern_exercise;

TEST(CommandPatternExerciseTest, SimpleTest) {
  Account a;
  Command command{Command::deposit, 100};
  a.process(command);

  ASSERT_EQ(100, a.balance);
  ASSERT_TRUE(command.success);

  command = Command{Command::withdraw, 50};
  a.process(command);

  ASSERT_EQ(50, a.balance);
  ASSERT_TRUE(command.success);

  command = Command{Command::withdraw, 150};
  a.process(command);

  ASSERT_EQ(50, a.balance);
  ASSERT_FALSE(command.success);
}

}  // namespace
