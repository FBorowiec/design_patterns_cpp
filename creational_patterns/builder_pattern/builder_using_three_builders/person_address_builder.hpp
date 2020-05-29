#ifndef DESIGN_PATTERNS_CREATION_PATTERNS_BUILDER_PATTERN_BUILDER_USING_THREE_BUILDERS_PERSON_ADDRESS_BUILDER_HPP
#define DESIGN_PATTERNS_CREATION_PATTERNS_BUILDER_PATTERN_BUILDER_USING_THREE_BUILDERS_PERSON_ADDRESS_BUILDER_HPP

#include <string>

#include "person_builder.hpp"

namespace creational {
namespace builder_using_three_builders {

class PersonAddressBuilder : public PersonBuilderBase {
 public:
  explicit PersonAddressBuilder(Person& person) : PersonBuilderBase{person} {}

  PersonAddressBuilder& WithStreetAddress(std::string street_address) {
    person_.street_address = street_address;
    return *this;
  }

  PersonAddressBuilder& WithPostCode(std::string post_code) {
    person_.post_code = post_code;
    return *this;
  }

  PersonAddressBuilder& WithCity(std::string city) {
    person_.city = city;
    return *this;
  }
};

}  // namespace builder_using_three_builders
}  // namespace creational

#endif  // DESIGN_PATTERNS_CREATION_PATTERNS_BUILDER_PATTERN_BUILDER_USING_THREE_BUILDERS_PERSON_ADDRESS_BUILDER_HPP
