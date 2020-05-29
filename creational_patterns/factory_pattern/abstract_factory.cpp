/**
 * Family of factories which use polymorphism to allow you to call the different factories.
 */
#include <functional>
#include <iostream>
#include <memory>
#include <unordered_map>

namespace creational {
namespace abstract_factory_pattern {

// Family of Products-------------------------------------------------------------------------------------------------|
struct HotDrink {
  virtual ~HotDrink() = default;
  virtual void Prepare(int volume) = 0;
};

struct Tea : HotDrink {
  void Prepare(int volume) override { std::cout << "Take tea bag, boil water, pour " << volume << "ml\n"; }
};

struct Coffee : HotDrink {
  void Prepare(int volume) override { std::cout << "Grind some beans, boil water, pour " << volume << "ml\n"; }
};

// Abstract Factory---------------------------------------------------------------------------------------------------|
struct HotDrinkFactory {
  virtual std::unique_ptr<HotDrink> make() const = 0;
};

// Family of Factories
struct TeaFactory : public HotDrinkFactory {
  std::unique_ptr<HotDrink> make() const override { return std::make_unique<Tea>(); }
};

struct CoffeeFactory : public HotDrinkFactory {
  std::unique_ptr<HotDrink> make() const override { return std::make_unique<Coffee>(); }
};

// Custom structure to create hot drinks -----------------------------------------------------------------------------|
class DrinkFactory {
 public:
  DrinkFactory() {
    hot_factories["Coffee"] = std::make_unique<CoffeeFactory>();
    hot_factories["Tea"] = std::make_unique<TeaFactory>();
  }

  std::unique_ptr<HotDrink> MakeDrink(const std::string& name) {
    auto drink = hot_factories[name]->make();
    drink->Prepare(200);
    return drink;
  }

 private:
  std::unordered_map<std::string, std::unique_ptr<HotDrinkFactory>> hot_factories;
};

// Functional Factory
class DrinkWithVolumeFactory {
 public:
  DrinkWithVolumeFactory() {
    factories["Tea"] = [] {
      auto tea = std::make_unique<Tea>();
      tea->Prepare(200);
      return tea;
    };

    factories["Coffee"] = [] {
      auto coffee = std::make_unique<Coffee>();
      coffee->Prepare(200);
      return coffee;
    };
  }

  std::unique_ptr<HotDrink> MakeDrink(const std::string& name) { return factories[name](); }

 private:
  std::unordered_map<std::string, std::function<std::unique_ptr<HotDrink>()>> factories;
};

}  // namespace abstract_factory_pattern
}  // namespace creational

// TEST---------------------------------------------------------------------------------------------------------------|

#include <iostream>

#include "gtest/gtest.h"

namespace {

using namespace creational::abstract_factory_pattern;

TEST(AbstractFactoryPatternTest, UsageOfTheAbstractFactory) {
  DrinkFactory df;
  df.MakeDrink("Coffee");

  DrinkWithVolumeFactory dwvf;
  df.MakeDrink("Tea");
}

}  // namespace
