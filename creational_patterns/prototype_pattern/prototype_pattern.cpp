/**
 * When it's easier to copy an existing object to fully initialize a new one.
 *
 * MOTIVATION:
 *  - Complicated objects (e.g., cars) aren't designed from scratch:
 *     & They reiterate existing designs
 *  - An existing (partially or fully constructed) design is a Prototype.
 *  - We make a copy (clone) of the prototype and customize it.
 *     & Requires 'deep copy' support
 *  - We make the cloning convenient (e.g., via a Factory)
 *
 * DESCRIPTION:
 * A partially or fully initialized object that you copy (clone) and make use of.
 *  - To clone it means you need to implement your own deep copy funciontality
 */
#include <iostream>
#include <memory>
#include <string>

namespace creational
{
namespace prototype_pattern
{

struct Address
{
  Address(const std::string& street, const std::string& city, const int suite) : street(street), city(city), suite(suite) {}

  friend std::ostream& operator<<(std::ostream& os, const Address& address)
  {
    os << "Street: " << address.street << "\nCity: " << address.city << "\nSuite: " << address.suite;
    return os;
  }

  std::string street, city;
  int suite;
};

struct Contact
{
  Contact(const std::string& name, std::unique_ptr<Address> address) : name(name), address(std::move(address)) {}
  Contact(const Contact& other) : name(other.name)
  {
    address = std::make_unique<Address>(other.address->street,
                                        other.address->city,
                                        other.address->suite);
  }
  ~Contact() {}

  friend std::ostream& operator<<(std::ostream& os, const Contact& contact)
  {
    os << "Name: " << contact.name << "\n" << *contact.address;
    return os;
  }

  std::string name;
  std::unique_ptr<Address> address;
};

struct EmployeeFactory
{
 public:
  static std::unique_ptr<Contact> NewMainOfficeEmployee(const std::string& name, const int suite)
  {
    auto main_address_ptr = std::make_unique<Address>("123 East Dr", "London", 0);
    static Contact main{"", std::move(main_address_ptr)};
    return NewEmployee(name, suite, main);
  }

  static std::unique_ptr<Contact> NewAuxOfficeEmployee(const std::string& name, const int suite)
  {
    auto aux_address_ptr = std::make_unique<Address>("321 West Dr", "London", 0);
    static Contact aux{"", std::move(aux_address_ptr)};
    return NewEmployee(name, suite, aux);
  }

 private:
  static std::unique_ptr<Contact> NewEmployee(const std::string& name, const int suite, const Contact& prototype)
  {
    auto result = std::make_unique<Contact>(prototype);
    result->name = name;
    result->address->suite = suite;
    return result;
  }
};

}  // namespace prototype_pattern
}  // namespace creational

// TEST---------------------------------------------------------------------------------------------------------------|

#include "gtest/gtest.h"

namespace
{

using namespace creational::prototype_pattern;

TEST(PrototypePatternTest, UsagesOfThePrototypePattern)
{
  auto addr = std::make_unique<Address>("123 East Dr", "London", 123);
  Contact john{"John Doe", std::move(addr)};
  // Instead of creating a lot more people inside the same address like that:
  //Contact jane{"Jane Smith", Address{"123 East Dr", "London", 103}};
  //Contact robert{"Robert De Niro", Address{"123 East Dr", "London", 111}};

  // It's better to make a copy of the object and just make the needed modifications:
  auto jane = john;
  jane.name = "Jane Smith";
  jane.address->suite = 103;

  std::cout << john << std::endl << jane << std::endl;
}

TEST(PrototypePatternTest, UsagesOfThePrototypePatternWithFactory)
{
  auto john = EmployeeFactory::NewMainOfficeEmployee("John", 123);
  auto bob = EmployeeFactory::NewAuxOfficeEmployee("Robert De Niro", 99);
  std::cout << *john << std::endl << *bob << std::endl;
}

}  // namespace
