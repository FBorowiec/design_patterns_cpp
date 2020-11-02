/**
 * A combination lock is a lock that opens after the right digits have been entered. A lock is preprogrammed with a
 * combination (e.g. 12345) and the user is expected to enter this combination to unlock the lock.
 *
 * The lock has a status field that indicates the state of the lock. The rules are:
 *  - If the lock has just been locked (or at startup), the status is LOCKED.
 *  - If a digit has been entered, that digit is shown on the screen. As the user enters more digits, they are added to
 * Status.
 *  - If the user has entered the correct sequence of digits, the lock status changes to OPEN.
 *  - If the user enters and incorrect sequence of digits, the lock status changes to ERROR.
 *
 * Implement the CombinationLock class to enable this behavior. Be sure to test both correct and incorrect inputs.
 * Here is an expmae unit test for the lock:
 *
 * CombinationLock cl({1,2,3});
 * ASSERT_EQ("LOCKED", cl.status);
 * cl.enter_digit(1);
 * ASSERT_EQ("1", cl.status);
 * cl.enter_digit(2);
 * ASSERT_EQ("12", cl.status);
 * cl.enter_digit(3);
 * ASSERT_EQ("OPEN", cl.status);
 */
#include <iostream>
#include <string>
#include <vector>

namespace behavioral {
namespace state_pattern_exercise {

class CombinationLock {
 public:
  std::string status;

  CombinationLock(const std::vector<int> &combination) : combination_(combination) { reset(); }

  void enter_digit(int digit) {
    if (status == "LOCKED") status = "";
    status += std::to_string(digit);
    if (combination_[static_cast<long unsigned int>(digits_entered)] != digit) {
      failed = true;
    }
    digits_entered++;

    if (digits_entered == static_cast<int>(combination_.size())) status = failed ? "ERROR" : "OPEN";
  }

 private:
  void reset() {
    status = "LOCKED";
    digits_entered = 0;
    failed = false;
  }

  std::vector<int> combination_;
  int digits_entered{0};
  bool failed{false};
};

}  // namespace state_pattern_exercise
}  // namespace behavioral

// TEST---------------------------------------------------------------------------------------------------------------|
#include "gtest/gtest.h"

namespace {

using namespace behavioral::state_pattern_exercise;

TEST(StatePatternExerciseTest, TestSuccess) {
  CombinationLock cl({1, 2, 3});
  ASSERT_EQ("LOCKED", cl.status);

  cl.enter_digit(1);
  ASSERT_EQ("1", cl.status);

  cl.enter_digit(2);
  ASSERT_EQ("12", cl.status);

  cl.enter_digit(3);
  ASSERT_EQ("OPEN", cl.status);
}

TEST(StatePatternExerciseTest, TestFailure) {
  CombinationLock cl({1, 2, 3});
  ASSERT_EQ("LOCKED", cl.status);

  cl.enter_digit(1);
  ASSERT_EQ("1", cl.status);

  cl.enter_digit(2);
  ASSERT_EQ("12", cl.status);

  cl.enter_digit(5);
  ASSERT_EQ("ERROR", cl.status);
}

}  // namespace
