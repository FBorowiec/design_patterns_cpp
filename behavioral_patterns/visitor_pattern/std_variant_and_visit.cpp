#include <iostream>
#include <string>
#include <type_traits>
#include <variant>

namespace behavioral {
namespace visitor_pattern {

struct AddressPrinter {
 public:
  void operator()(const std::string& house_name) const { std::cout << "A house called " << house_name << std::endl; }

  void operator()(const int house_number) const { std::cout << "House number " << house_number << std::endl; }
};

}  // namespace visitor_pattern
}  // namespace behavioral

// TEST---------------------------------------------------------------------------------------------------------------|

#include "gtest/gtest.h"

namespace {

using namespace behavioral::visitor_pattern;

TEST(VisitorPatternTest, UsageOfTheStandardLibraryVisitors) {
  std::variant<std::string, int> house;
  house = "Monterfiore Castle";

  AddressPrinter ap;
  std::visit(ap, house);
}

/*
TEST(VisitorPatternTest, UsageOfALambdaInsideTheStdVisit) {
  std::variant<std::string, int> house;
  house = 123;

  // AddressPrinter ap;
  std::visit([](auto& arg) {
    using T = std::decay_t<decltype(arg)>;
    if constexpr (std::is_same_v<T, std::string>) {
      std::cout << "A house called " << arg.c_str() << std::endl;
    } else {
      std::cout << "House number " << arg << std::endl;
    }
  });
}
*/
}  // namespace
