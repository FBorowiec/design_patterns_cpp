/**
 * Connecting components together through abstractions.
 * MOTIVATION:
 * A Bridge prevents a 'Cartesian product' complexity explosion
 * Example:
 *  - Base class ThreadSchefuler
 *  - Can be preemptive or cooperative
 *  - Can run on Windows or Unix
 *  - End up with 2x2 scenario: WindowsPTS, UnitPTS, WindotwsCTS, UnixCTS
 * The Bridge pattern avoids the entity explosion.
 * It is a mechanism that decouples an interface (hierarchy) from an implementation (hierarchy).
 */
#include <iostream>
#include <string>

namespace structural
{
namespace bridge_pattern
{

/**
 * Pimpl idiom
 * The Pimpl idiom is also a manifestation of the Bridge design pattern.
 * It serves the purpose of hiding the implementation details of a particular
 * class by sneaking it into its own implementation class.
 */
class Person
{
 public:

  class PersonImpl;
  PersonImpl* impl;

  Person() : impl(new PersonImpl) {}
  ~Person() { delete PersonImpl; }

  void Greet();

  std::string name;
};

// Important NOT to have the Impl in the header file but hide it from the consumer in a cpp file----------------------|
class Person::PersonImpl
{
 public:
  void Greet(Person* p) { std::cout<<"Hello, my name is " << p->name << std::endl; }
};

void Person::Greet() { impl->Greet(this); }
/**
 * The user of the Person do not have to recompile whenever the implementation of PersonImpl changed.
 * This has the advantage therefore of improving compilation speed.
 * Also, you can hide any details you might not want to ship to the user inside PersonImpl.
 */

}  // namespace bridge_pattern
}  // namespace structural

// TEST---------------------------------------------------------------------------------------------------------------|

#include "gtest/gtest.h"

namespace
{

using namespace structural::bridge_pattern;

TEST(BridgePatternTest, UsageOfTheBridgePattern)
{

}

}  // namespace
