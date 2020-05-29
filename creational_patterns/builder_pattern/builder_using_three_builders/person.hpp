#ifndef DESIGN_PATTERNS_CREATION_PATTERNS_BUILDER_PATTERN_BUILDER_USING_THREE_BUILDERS_PERSON_HPP
#define DESIGN_PATTERNS_CREATION_PATTERNS_BUILDER_PATTERN_BUILDER_USING_THREE_BUILDERS_PERSON_HPP

#include <iostream>
#include <string>

#include "person_builder.hpp"

namespace creational {
namespace builder_using_three_builders {

class Person {
 public:
  ~Person() {}
  // Builders
  static PersonBuilder Create() { return PersonBuilder{}; };

  Person(Person&& other)
      : street_address{std::move(other.street_address)},
        post_code{std::move(other.post_code)},
        city{std::move(other.city)},
        company_name{std::move(other.company_name)},
        position(std::move(other.position)),
        annual_income(other.annual_income) {}

  Person& operator=(Person&& other) {
    if (this == other) return *this;
    street_address = std::move(other.street_address);
    post_code = std::move(other.post_code);
    city = std::move(other.city);
    company_name = std::move(other.company_name);
    position = std::move(other.position);
    annual_income = other.annual_income);
    return *this;
  }

  friend std::ostream& operator<<(std::ostream& os, const Person& p) {
    return os << "Street address: " << p.street_address << "\nPost code: " << p.post_code << "\nCity: " << p.city
              << "\nCompany name: " << p.company_name << "\nPosition: " << p.position
              << "\nAnnual income: " << p.annual_income;
  }

  friend class PersonBuilder;
  friend class PersonJobBuilder;
  friend class PersonAddressBuilder;

 private:
  Person() {}
  // Address
  std::string street_address, post_code, city;
  // Employment
  std::string company_name, position;
  int annual_income{0};
};

}  // namespace builder_using_three_builders
}  // namespace creational

#endif  // DESIGN_PATTERNS_CREATION_PATTERNS_BUILDER_PATTERN_BUILDER_USING_THREE_BUILDERS_PERSON_HPP
