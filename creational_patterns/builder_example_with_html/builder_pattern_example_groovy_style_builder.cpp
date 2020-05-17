/**
 * SECOND EXAMPLE!
 * Please refer to the first example for more details.
 */
#include <iostream>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>

namespace creational
{
namespace builder_pattern_groovy
{

struct Tag
{
  std::string name, text;
  std::vector<Tag> children;
  std::vector<std::pair<std::string, std::string>> attributes;

  // API for printing
  friend std::ostream& operator<<(std::ostream& os, const Tag& tag)
  {
    os << "<" << tag.name;

    for (const auto& att : tag.attributes)
      os << " " << att.first << "=\"" << att.second <<"\"";

    if (tag.children.size() == 0 && tag.text.length() == 0)
      os << "/>" << std::endl;
    else
    {
      os << ">" << std::endl;

      if (tag.text.length())
        os << tag.text << std::endl;

      for (const auto& child : tag.children)
        os << child;

      os << "</" << tag.name << ">" << std::endl;
    }

    return os;
  }

 protected:
  Tag(const std::string& name, const std::string& text) : name(name), text(text) {}
  Tag(const std::string& name, const std::vector<Tag>& children) : name(name), children(children) {}
};

struct P : Tag  // Paragraph
{
  P (const std::string& text) : Tag("p", text) {}
  P (std::initializer_list<Tag> children) : Tag{"p", children} {}
};

struct IMG : Tag
{
  explicit IMG (const std::string& url) : Tag{"img", ""}
  {
    attributes.emplace_back(std::make_pair("src", url));
  }
};

}  // builder_pattern_groovy
}  // creational

// TEST---------------------------------------------------------------------------------------------------------------|

#include "gtest/gtest.h"

namespace
{

using namespace creational::builder_pattern_groovy;

TEST(GroovyBuilderPatternTest, GroovyBuilderConstructionExample)
{
  std::cout << P {
    IMG { "https://avatars2.githubusercontent.com/u/172399?s=460&u=e25354f3b153d250e035ed1a9097142176d02101&v=4"}
  } << std::endl;
}

}  // namespace
