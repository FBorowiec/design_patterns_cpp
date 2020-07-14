#include <iostream>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>

namespace creational {
namespace builder_pattern_groovy {

struct Tag {
  std::string name_, text_;
  std::vector<Tag> children_;
  std::vector<std::pair<std::string, std::string>> attributes;

  // API for printing
  friend std::ostream& operator<<(std::ostream& os, const Tag& tag) {
    os << "<" << tag.name_;

    for (const auto& att : tag.attributes) os << " " << att.first << "=\"" << att.second << "\"";

    if (tag.children_.size() == 0 && tag.text_.length() == 0)
      os << "/>" << std::endl;
    else {
      os << ">" << std::endl;

      if (tag.text_.length()) os << tag.text_ << std::endl;

      for (const auto& child : tag.children_) os << child;

      os << "</" << tag.name_ << ">" << std::endl;
    }

    return os;
  }

 protected:
  Tag(const std::string& name, const std::string& text) : name_(name), text_(text) {}
  Tag(const std::string& name, const std::vector<Tag>& children) : name_(name), children_(children) {}
};

struct P : Tag  // Paragraph
{
  P(const std::string& text) : Tag("p", text) {}
  P(std::initializer_list<Tag> children) : Tag{"p", children} {}
};

struct IMG : Tag {
  explicit IMG(const std::string& url) : Tag{"img", ""} { attributes.emplace_back(std::make_pair("src", url)); }
};

}  // namespace builder_pattern_groovy
}  // namespace creational

// TEST---------------------------------------------------------------------------------------------------------------|

#include "gtest/gtest.h"

namespace {

using namespace creational::builder_pattern_groovy;

TEST(GroovyBuilderPatternTest, GroovyBuilderConstructionExample) {
  std::cout
      << P{IMG{"https://avatars2.githubusercontent.com/u/172399?s=460&u=e25354f3b153d250e035ed1a9097142176d02101&v=4"}}
      << std::endl;
}

}  // namespace
