/**
 * A multiton is another variation of the singleton but instead of preventing
 * the creation of multiple instances it keeps a max value of the instantiation.
 */
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>

namespace creational {
namespace multiton_pattern {

enum class Importance { primnary, secondary, tertiary };

template <typename T, typename Key = std::string>
class Multiton {
 public:
  static std::shared_ptr<T> Get(const Key& key) {
    if (const auto it = instances.find(key); it != instances.end()) {
      return it->second;
    }

    auto instance = std::make_shared<T>();
    instances[key] = instance;
    return instance;
  }

 protected:
  Multiton() = default;
  virtual ~Multiton() = default;

 private:
  static std::unordered_map<Key, std::shared_ptr<T>> instances;
};

template <typename T, typename Key>
std::unordered_map<Key, std::shared_ptr<T>> Multiton<T, Key>::instances;

class Printer {
 public:
  Printer() {
    ++Printer::total_instance_count;
    std::cout << "A total of " << Printer::total_instance_count << " instances created so far\n";
  }

 private:
  static int total_instance_count;
};

int Printer::total_instance_count = 0;

}  // namespace multiton_pattern
}  // namespace creational

// TEST---------------------------------------------------------------------------------------------------------------|

#include "gtest/gtest.h"

namespace {

using namespace creational::multiton_pattern;

TEST(MonostateTest, UsageOfMonostate) {
  using mt = Multiton<Printer, Importance>;

  auto main = mt::Get(Importance::primnary);
  auto aux = mt::Get(Importance::secondary);
  auto aux2 = mt::Get(Importance::secondary);  // This instance won't be created!
}

}  // namespace
