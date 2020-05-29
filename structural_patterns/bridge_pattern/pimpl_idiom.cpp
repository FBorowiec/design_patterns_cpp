/**
 * Pimpl idiom
 * The Pimpl idiom is also a manifestation of the Bridge design pattern.
 * It serves the purpose of hiding the implementation details of a particular
 * class by sneaking it into its own implementation class.
 */
#include <iostream>
#include <memory>
#include <string>

namespace structural {
namespace bridge_pattern {

class Person {
 public:
  /**
   * The user of the Person do not have to recompile whenever the implementation of PersonImpl changed.
   * This has the advantage therefore of improving compilation speed.
   * Also, you can hide any details you might not want to ship to the user inside PersonImpl.
   */
  class PersonImpl;
  std::unique_ptr<PersonImpl> impl;

  Person() : impl(std::move(std::make_unique<PersonImpl>())) {}
  ~Person() {}

  void Greet();

  std::string name;
};

// Important NOT to have the Impl in the header file but hide it from the consumer in a cpp file----------------------|
class Person::PersonImpl {
 public:
  void Greet(Person* p) { std::cout << "Hello, my name is " << p->name << std::endl; }
};

void Person::Greet() { impl->Greet(this); }

}  // namespace bridge_pattern
}  // namespace structural
