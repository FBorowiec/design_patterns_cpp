/**
 * INTENT:
 * Typically a tool for structure traversal rather than anything else.
 * MOTIVATION:
 * Need to define a new operation on an entire class hierarchy:
 *  - e.g. make a document model printable to HTML/Markdown
 * Do not want to keep modifying every class in the hierarchy (open-close principle and single-responsibility).
 * Need access to the non-common aspects of classes in the hierarchy.
 *  - Cannot put everything into a single interface
 * Create an external component to handle rendering.
 *  - But preferably avoid type checks
 *
 * The Visitor Pattern is when a component (visitor) is allowed to travers teh entire inheritance hierarchy.
 * Implemented by propagating a single visit() method throught the entire hierarchy.
 */
#include <iostream>

namespace behavioral {
namespace visitor_pattern {



}  // namespace visitor_pattern
}  // namespace behavioral

// TEST---------------------------------------------------------------------------------------------------------------|

#include "gtest/gtest.h"

namespace {

using namespace behavioral::visitor_pattern;

TEST(VisitorPatternTest, UsageOfTheVisitorPattern) {
}

}  // namespace
