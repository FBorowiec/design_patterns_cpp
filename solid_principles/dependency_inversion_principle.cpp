/**
 * A. High-level modules should not depend on low-level modules.
 *    Both should depend on abstractions.
 * B. Abstractions should not depend on details.
 *    Details should depend on abstractions.
 *
 * *Abstractions - Interfaces or Base classes
 */
#include <iostream>
#include <string>
#include <tuple>
#include <vector>

namespace solid_principles {
namespace dependency_inverstion_principle {

enum class Relationship { parent, child, sibling };

struct Person {
  std::string name;
};

namespace bad {
struct Relationships  // low-level module
{
  std::vector<std::tuple<Person, Relationship, Person>> relations{};

  void AddParentAndChild(const Person& parent, const Person& child) {
    relations.push_back({parent, Relationship::parent, child});
    relations.push_back({child, Relationship::child, parent});
  }
};

struct Research  // high-level module
{
  /**
   * BAD! Dependency on a low-level module (Relationships) inside a high-level module.
   * BAD! Research accesses the details of the low-level module.
   */
  Research(Relationships& relationships) {
    /**
     * Now the high-level module Research depends on the implementation details
     * (here a vector of tuples) of the low-level module.
     */
    auto& relations = relationships.relations;
    for (auto&& [first, rel, second] : relations) {
      if (first.name == "John" && rel == Relationship::parent) {
        std::cout << "John has a child called " << second.name << std::endl;
      }
    }
  }
};
}  // namespace bad

namespace good {
struct RelationshipsBrowser {
  virtual std::vector<Person*> FindAllChildrenOf(const std::string& name) = 0;
};

struct Relationships : public RelationshipsBrowser  // low-level module
{
  std::vector<std::tuple<Person, Relationship, Person>> relations{};

  void AddParentAndChild(const Person& parent, const Person& child) {
    relations.push_back({parent, Relationship::parent, child});
    relations.push_back({child, Relationship::child, parent});
  }

  std::vector<Person*> FindAllChildrenOf(const std::string& name) override {
    std::vector<Person*> result{};
    for (auto&& [first, rel, second] : relations) {
      if (first.name == name && rel == Relationship::parent) result.push_back(&second);
    }
    return result;
  }
};

struct Research {
  Research(RelationshipsBrowser& browser) {
    for (auto& child : browser.FindAllChildrenOf("John")) {
      std::cout << "John has a child called " << child->name << std::endl;
    }
  }
};
}  // namespace good

}  // namespace dependency_inverstion_principle
}  // namespace solid_principles

// TEST---------------------------------------------------------------------------------------------------------------|

#include "gtest/gtest.h"

namespace {

using namespace solid_principles::dependency_inverstion_principle;

TEST(DependencyInversionPrincipleTest, ViolationOfTheDIPexample) {
  Person parent{"John"};
  Person child1{"Chris"}, child2{"Matt"};

  bad::Relationships relationships;
  relationships.AddParentAndChild(parent, child1);
  relationships.AddParentAndChild(parent, child2);

  bad::Research r(relationships);
  /**
   * This works only as long as the low-level module doesn't hid the relations vector of tuples
   * or the container changes completely.
   */
}

TEST(DependencyInversionPrincipleTest, ProperFollowingOfTheDIPexample) {
  /**
   * Code needs no change.
   * It is better to have dependencies on abstraction rather than concrete implementations.
   * If the low-level module changes it won't break the high-level module.
   */
  Person parent{"John"};
  Person child1{"Chris"}, child2{"Matt"};

  good::Relationships relationships;
  relationships.AddParentAndChild(parent, child1);
  relationships.AddParentAndChild(parent, child2);

  good::Research r(relationships);
}

}  // namespace
