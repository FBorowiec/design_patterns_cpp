/**
 * You are given the Person class and asked to write a ResponsiblePerson wrapper/proxy that does the following:
 *  - Allows person to drink unless they are younger than 18 (in that case, return "too young")
 *  - Allows person to drink unless they are younger than 16 (in that case, return "too young")
 *  - In case of driving while drink, returns "dead"
 * The interface of ResponsiblePerson has to match that of Person, except for the constructor,
 * which takes an underlying Person object.
 */
#include <string>

namespace structural {
namespace proxy_pattern_exercise {

class Person {
 public:
  Person(int age) : age_(age) {}

  int get_age() const { return age_; }
  void set_age(int age) { this->age_ = age; }

  std::string drink() const { return "drinking"; }
  std::string drive() const { return "driving"; }
  std::string drink_and_drive() const { return "driving while drunk"; }

 protected:
  friend class ResponsiblePerson;

 private:
  int age_;
};

class ResponsiblePerson {
 public:
  ResponsiblePerson(const Person &person) : person_(person) {}
  void set_age(int age) { person_.set_age(age); }

  std::string drink() const { return person_.get_age() >= 18 ? person_.drink() : "too young"; }
  std::string drive() const { return person_.get_age() >= 16 ? person_.drive() : "too young"; }
  std::string drink_and_drive() const { return "dead"; }

 private:
  Person person_;
};

}  // namespace proxy_pattern_exercise
}  // namespace structural

// TEST---------------------------------------------------------------------------------------------------------------|
#include "gtest/gtest.h"

namespace {

using namespace structural::proxy_pattern_exercise;

TEST(ProxyPatternExerciseTest, BaselineTest) {
  Person p{10};
  ResponsiblePerson rp{p};

  ASSERT_EQ("too young", rp.drive());
  ASSERT_EQ("too young", rp.drink());
  ASSERT_EQ("dead", rp.drink_and_drive());

  rp.set_age(20);

  ASSERT_EQ("driving", rp.drive());
  ASSERT_EQ("drinking", rp.drink());
  ASSERT_EQ("dead", rp.drink_and_drive());
}

}  // namespace
