/**
 * A construct which adapts an existing interface X to conform to the required interface Y.
 * You need to determine the API you have and the API you need.
 * Create a component which aggregates (has a reference to, ...) the adaptee.
 * Intermediate representations can pile up: use chaching and other optimizations.
 */
#include <algorithm>
#include <iostream>
#include <memory>
#include <string>

namespace structural {
namespace adapter_pattern {

/**
 * The Target defines the domain-specific interface used by the client code.
 */
class Target {
 public:
  virtual ~Target() = default;

  virtual std::string Request() const { return "Target: The default target's behavior."; }
};

/**
 * The Adaptee contains some useful behavior, but its interface is incompatible
 * with the existing client code. The Adaptee needs some adaptation before the
 * client code can use it.
 */
class Adaptee {
 public:
  std::string SpecificRequest() const { return ".eetpadA eht fo roivaheb laicepS"; }
};

/**
 * The Adapter makes the Adaptee's interface compatible with the Target's
 * interface.
 */
class Adapter : public Target {
 private:
  std::unique_ptr<Adaptee> adaptee_;

 public:
  Adapter(std::unique_ptr<Adaptee> adaptee) : adaptee_(std::move(adaptee)) {}

  std::string Request() const override {
    std::string to_reverse = this->adaptee_->SpecificRequest();
    std::reverse(to_reverse.begin(), to_reverse.end());
    return "Adapter: (TRANSLATED) " + to_reverse;
  }
};

}  // namespace adapter_pattern
}  // namespace structural

// TEST---------------------------------------------------------------------------------------------------------------|

#include "gtest/gtest.h"

namespace {

using namespace structural::adapter_pattern;

/**
 * The client code supports all classes that follow the Target interface.
 */
void ClientCode(const std::unique_ptr<Target> target) {
  if (!target) {
    return;
  }
  std::cout << target->Request();
}

TEST(AdapterPatternTest, UsageOfTheAdapterPattern) {
  std::cout << "Client: I can work just fine with the Target objects:\n";
  auto target = std::make_unique<Target>();
  ClientCode(std::move(target));

  std::unique_ptr<Adaptee> adaptee;
  std::cout << "\n\nClient: The Adaptee class has a weird interface. See, I don't understand it:\n";
  std::cout << "Adaptee: " << adaptee->SpecificRequest();

  std::cout << "\n\nClient: But I can work with it via the Adapter:\n";
  std::unique_ptr<Adapter> adapter = std::make_unique<Adapter>(std::move(adaptee));

  ClientCode(std::move(adapter));
  std::cout << "\n";
}

}  // namespace
