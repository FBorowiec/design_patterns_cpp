#include "gtest/gtest.h"

#include "person.hpp"
#include "person_address_builder.hpp"
#include "person_builder.hpp"
#include "person_job_builder.hpp"

namespace {

using namespace creational::builder_using_three_builders;

TEST(PersonBuilderTest, PersonConstructionUsingThreeBuilders) {
  Person p = Person::Create()
                 .Lives()
                 .WithStreetAddress("123 London Road")
                 .WithPostCode("SW1 1GB")
                 .WithCity("London")
                 .Works()
                 .WithCompanyName("PragmaSoft")
                 .WithPosition("Consultant")
                 .WithAnnualIncome(10e6);

  std::cout << p << std::endl;
}

}  // namespace
