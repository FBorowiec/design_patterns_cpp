/**
 * A particular form of a singleton where all the data storage is static.
 * It is a bad idea:
 *  - no inheritance possible
 *  - users might get very confused
 */
namespace creational {
namespace monostate_pattern {

class Printer {
 public:
  int GetId() const { return id; }
  void SetId(int value) { id = value; }

 private:
  static int id;
};
int Printer::id = 1;

}  // namespace monostate_pattern
}  // namespace creational

// TEST---------------------------------------------------------------------------------------------------------------|

#include "gtest/gtest.h"

namespace {

using namespace creational::monostate_pattern;

TEST(MonostateTest, UsageOfMonostate) {
  Printer p;
  int id = p.GetId();

  Printer p2;  // Printer p2 is actually going to use the same data

  (void)id;
  (void)p2;
}

}  // namespace
