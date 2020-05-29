#ifndef DESIGN_PATTERNS_CREATION_PATTERNS_BUILDER_PATTERN_BUILDER_USING_THREE_BUILDERS_PERSON_BUILDER_HPP
#define DESIGN_PATTERNS_CREATION_PATTERNS_BUILDER_PATTERN_BUILDER_USING_THREE_BUILDERS_PERSON_BUILDER_HPP

#include "person.hpp"

namespace creational {
namespace builder_using_three_builders {

class PersonAddressBuilder;
class PersonJobBuilder;

class PersonBuilderBase {
 public:
  PersonAddressBuilder Lives() const { return PersonAddressBuilder{person_}; }
  PersonJobBuilder Works() const { return PersonJobBuilder{person_}; }
  operator Person() const { return std::move(person_); }

 protected:
  explicit PersonBuilderBase(Person& person) : person_(person) {}
  Person& person_;
};

// The only reason there is a PersonBuilder is not to have many duplications of person at each inheritance level
class PersonBuilder : public PersonBuilderBase {
 public:
  PersonBuilder() : PersonBuilderBase{person} {}

 private:
  Person person;
};

}  // namespace builder_using_three_builders
}  // namespace creational

#endif  // DESIGN_PATTERNS_CREATION_PATTERNS_BUILDER_PATTERN_BUILDER_USING_THREE_BUILDERS_PERSON_BUILDER_HPP
