/**
 * "When discussing which patterns to drop,
 *  we found that we still love them all.
 *  (Not really - I'm in favor of dropping Singleton.
 *  Its use is almost always a design smell." - Erich Gamma
 *
 * MOTIVATION:
 *  - For some components it only makes sense to have one in the system e.g.:
 *     & Database repository
 *     & Object factory
 *  - E.g. the constructor call is expensive
 *     & We only do it once
 *     & We provide everyone with the same instance
 *  - Want to prevent anyone creating additional copies
 *  - Need to take care of lazy instantiation and thread safety
 *
 * DESCRIPTION:
 * A component which is instantiated only once.
 * Making a 'safe' singleton needs:
 *  - Hiding or deleting the type's constructor, copy constructor
 *    and copy assignment operators
 *  - Create a static method that returns a reference to a static member
 *  - Guaranteed to be thread-safe since C++11
 * Types with 'hard' dependencies on singletons are difficult to test:
 *  - Cannot decouple the singleton and supply a fake object
 * Instead of directly using a singleton, consider depending on an abstraction (eg. an interface)
 * Consider defining singleton lifetime in DI container.
 */
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

namespace creational {
namespace singleton_pattern {

/**
 * Dependency injection for testing the singleton's methods.
 */
class Database {
 public:
  virtual int GetPopulation(const std::string& name) = 0;
};

class SingletonDatabase : public Database {
 public:
  SingletonDatabase(SingletonDatabase const&) = delete;
  void operator=(SingletonDatabase const&) = delete;

  static SingletonDatabase& Get() {
    static SingletonDatabase sdb;
    return sdb;
  }

  int GetPopulation(const std::string& name) override { return capitals[name]; }

 private:
  SingletonDatabase() {
    std::ifstream ifs("capitals.txt", std::ios::in);
    std::string s, s2;

    while (std::getline(ifs, s)) {
      std::getline(ifs, s2);
      int population = std::stoi(s2);
      capitals[s] = population;
    }
  }

  std::unordered_map<std::string, int> capitals;
};

class DummyDatabase : public Database {
  std::unordered_map<std::string, int> capitals;

 public:
  DummyDatabase() {
    capitals["alpha"] = 1;
    capitals["beta"] = 2;
    capitals["gamma"] = 3;
  }

  int GetPopulation(const std::string& name) override { return capitals[name]; }
};

struct SingletonRecordFinder {
  int TotalPopulation(std::vector<std::string> names) {
    int result{0};
    for (auto& name : names) result += SingletonDatabase::Get().GetPopulation(name);
    return result;
  }
};

struct ConfigurableSingletonRecordFinder {
  Database& db_;
  ConfigurableSingletonRecordFinder(Database& db) : db_(db) {}

  int TotalPopulation(std::vector<std::string> names) {
    int result{0};
    for (auto& name : names) result += db_.GetPopulation(name);
    return result;
  }
};

}  // namespace singleton_pattern
}  // namespace creational

// TEST----------------------------------------------------------------------------------------------------------------|

#include "gtest/gtest.h"

namespace {

using namespace creational::singleton_pattern;

TEST(SingletonPatternTest, UsageOfTheSingletonPattern) {
  std::string city = "Tokyo";
  std::cout << city << " has population " << SingletonDatabase::Get().GetPopulation(city) << std::endl;
}

/**
 * Here a dangerous thing happens. The test is strongly tied to the actual database (capitals.txt),
 * which makes it more of an integration test than a unit test.
 */
TEST(RecordFinderTest, DISABLED_SingletonTotalPopulationTest) {
  SingletonRecordFinder rf;
  std::vector<std::string> names{"Seoul", "Mexico City"};

  int tp = rf.TotalPopulation(names);

  EXPECT_EQ(17400000 + 17500000, tp);
}

/**
 * The solution is to create a dummy database inheriting from the base database only the methods to be tested.
 * Then a configurable record finder can therefore test the needed functionalities.
 */
TEST(RecordFinderTest, DependantPopulationTest) {
  DummyDatabase db;
  ConfigurableSingletonRecordFinder rf{db};

  EXPECT_EQ(4, rf.TotalPopulation(std::vector<std::string>{"alpha", "gamma"}));
}

}  // namespace
