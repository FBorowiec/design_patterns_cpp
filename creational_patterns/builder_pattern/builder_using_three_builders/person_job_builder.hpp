#ifndef DESIGN_PATTERNS_CREATION_PATTERNS_BUILDER_PATTERN_BUILDER_USING_THREE_BUILDERS_PERSON_JOB_BUILDER_HPP
#define DESIGN_PATTERNS_CREATION_PATTERNS_BUILDER_PATTERN_BUILDER_USING_THREE_BUILDERS_PERSON_JOB_BUILDER_HPP

#include <string>

#include "person_builder.hpp"

namespace creational {
namespace builder_using_three_builders {

class PersonJobBuilder : public PersonBuilderBase {
 public:
  explicit PersonJobBuilder(Person& person) : PersonBuilderBase{person} {}

  PersonJobBuilder& WithCompanyName(std::string company_name) {
    person_.company_name = company_name;
    return *this;
  }

  PersonJobBuilder& WithPosition(std::string position) {
    person_.position = position;
    return *this;
  }

  PersonJobBuilder& WithAnnualIncome(int annual_income) {
    person_.annual_income = annual_income;
    return *this;
  }
};

}  // namespace builder_using_three_builders
}  // namespace creational

#endif  // DESIGN_PATTERNS_CREATION_PATTERNS_BUILDER_PATTERN_BUILDER_USING_THREE_BUILDERS_PERSON_JOB_BUILDER_HPP
