/**
 * How traversal of data structures happens and who makes it happen.
 * MOTIVATION:
 * Iteration (traversal) is a core functionality of various data.
 * An iterator is a class that facilitates the traversal:
 *  - Keeps a reference to the current element
 *  - Knows how to move to a different element
 * Can be used implicitely:
 *  - Range-based for loop
 *  - Coroutines
 *
 * The iterator is an object that facilitates the traversal of a data structure:
 *  - An object can be iterated (traversed) if it defines a begin() / end() pair.
 *  - An iterator specifies how you can traverse an object.
 *  - Typically requires implementation of the '!=' and '++' operators
 *  - '++' is called sporadically, so cannot be recursive but you can use coroutines
 *    (allowing recursion through generator-yielding functions)
 */
#include <iostream>
#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace behavioral {
namespace iterator_pattern {
namespace {

TEST(IteratorPatternTest, IteratorsInTheStandardTemplateLibrary) {
  std::vector<std::string> names{"John", "Jane", "Jill", "Jack"};

  // iterator over vector of strings
  std::vector<std::string>::iterator it = names.begin();  // auto
  std::cout << "First name is: " << *it << std::endl;

  ++it;
  it->append(std::string(" Goodall"));
  std::cout << "Second name is: " << *it << std::endl;

  while (++it != names.end()) {
    std::cout << "Another name: " << *it << std::endl;
  }

  // reverse iterator over vector of strings
  for (auto ri = std::rbegin(names); ri != rend(names); ++ri) {
    std::cout << *ri;
    if (ri + 1 != std::rend(names)) std::cout << ", ";
  }
  std::cout << std::endl;

  // const reverse iterator over vector of strings
  std::vector<std::string>::const_reverse_iterator jack = std::crbegin(names);
  // *jack += std::string(" Reacher"); <-- FAILS!
  (void)jack;

  /**
   * Ranged-based for-loop:
   * begin/end
   * *it
   */
  for (auto&& name : names) {
    std::cout << "Name: " << name << std::endl;
  }
}

}  // namespace
}  // namespace iterator_pattern
}  // namespace behavioral
