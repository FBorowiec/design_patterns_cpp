/**
 * You are given a class called Person. The person has two fields: id, and name.
 * Implement a non-static PersonFactory that has a create_person() method that takes a person's name.
 * The id of the person should be set as a 0-based index of the object created.
 * So, the first person the factory makes should have id=0, second id=1 and so on.
 */
#include <string>

namespace creational {
namespace factory_pattern_exercise {

struct Person {
  int id;
  std::string name;
};

class PersonFactory {
  int id{0};

 public:
  Person create_person(const std::string& name) { return {id++, name}; }
};

}  // namespace factory_pattern_exercise
}  // namespace creational

// TEST---------------------------------------------------------------------------------------------------------------|
#include "gtest/gtest.h"

namespace {

using namespace creational::factory_pattern_exercise;

TEST(PersonFactoryTest, SimplePersonTest) {
  PersonFactory pf;

  auto p1 = pf.create_person("Chris");
  ASSERT_EQ("Chris", p1.name);

  auto p2 = pf.create_person("Sarah");
  ASSERT_EQ(1, p2.id) << "Expected the second created person's id to be = 1";
}

}  // namespace
