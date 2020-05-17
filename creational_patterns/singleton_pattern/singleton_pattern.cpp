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
 */
#include <iostream>
#include <string>
#include <unordered_map>

namespace creational
{
namespace singleton_pattern
{

class SingletonDatabase
{
 public:
  SingletonDatabase(SingletonDatabase const&) = delete;
  void operator=(SingletonDatabase const&) = delete;

  static SingletonDatabase& Get()
  {
    static SingletonDatabase sdb;
    return sdb;
  }

  int GetPopulation(const std::string& name)
  {
    return capitals[name];
  }

 private:
  SingletonDatabase()
  {
    std::cout << "Initializing database\n";
    std::ifstream ifs("capitals.txt");
    std::string s, s2;

    while(getline(ifs, s))
    {
      getline(ifs, s2);
      int population = std::stoi(s2);
      capitals[s] = population;
    }
  }

  std::unordered_map<std::string, int> capitals;
};

}  namespace  // singleton_pattern
}  namespace  // creational

//TEST----------------------------------------------------------------------------------------------------------------|

#include "gtest/gtest.h"

namespace
{

using namespace creational::singleton_pattern;

TEST(SingletonPatternTest, UsageOfTheSingletonPattern)
{
  std::string city = "Tokyo";
  std::cout << city << " has population " <<  SingletonDatabase::Get().GetPopulation("Tokyo");
}

}  // namespace
