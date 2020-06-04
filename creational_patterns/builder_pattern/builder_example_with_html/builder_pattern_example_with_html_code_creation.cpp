/**
 * When piecewise object construction is complicated,
 * provide and API for doing it succinctly.
 *
 * Some objects are simple and can be created in a single constructor call.
 * Other objects require a lot of ceremony to create.
 * Havin an object with (e.g.) 10 constructor arguments is not productive.
 * Instead, opt for piecewise construction.
 * The Builder pattern provides an API for constructing an object step-by-step.
 */
#include <cstdint>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace creational {
namespace builder_pattern {

namespace bad {
// BAD! String needs to be build piece-by-piece.
void FunctionWithoutBuilder() {
  auto text = "hello";
  std::string output{};
  output += "<p>";
  output += text;
  output += "</p>";
  std::cout << output << std::endl;
}

// BAD! Slighlty better but still piece-by-piece approach.
void AnotherFunctionWithoutBuilder() {
  std::string words[] = {"hello", "world"};
  std::ostringstream oss;
  oss << "<ul>\n";
  for (auto w : words) oss << " <li>" << w << "</li>\n";
  oss << "</ul>\n";
  std::cout << oss.str() << std::endl;
}
}  // namespace bad

namespace good {
struct HtmlElement {
  // API for printing elements
  std::string str(int indent = 0) const {
    std::ostringstream oss{};
    std::string i(indent_size * static_cast<long unsigned int>(indent), ' ');
    oss << i << "<" << name_ << ">" << std::endl;
    if (text_.size() > 0)
      oss << std::string(indent_size * static_cast<long unsigned int>(indent + 1), ' ') << text_ << std::endl;

    for (const auto& e : elements) oss << e.str(indent + 1);

    oss << i << "</" << name_ << ">" << std::endl;
    return oss.str();
  }

 private:
  /**
   * Making the constructors of HtmlElement private
   * forces the user to go through the Builder to obtain an HtmlElement.
   * Unfortunately it breaks the HtmlBuilder as it does not have access to any constructor.
   */
  HtmlElement() {}
  HtmlElement(const std::string& name, const std::string& text) : name_(name), text_(text) {}

 public:
  /**
   * In order to bypass the issue of having the constructors private
   * we can add the HtmlBuilder as a friend class
   */
  friend class HtmlBuilder;

 private:
  std::string name_{}, text_{};
  std::vector<HtmlElement> elements{};
  const size_t indent_size = 2;
};

// API for building the elements - BUILDER PATTERN
class HtmlBuilder {
  HtmlElement root{};

 public:
  HtmlBuilder(std::string root_name) { root.name_ = root_name; }

  /**
   * FLUENT BUILDER.
   * Very common in the builder pattern. It allows successive calls one after another of the AddChild method.
   * To make a fluent interface you need to change the return type
   * from void to a pointer or a reference to the type you are currently in.
   */
  HtmlBuilder& AddChild(std::string child_name, std::string child_text) {
    HtmlElement e{child_name, child_text};
    root.elements.emplace_back(e);
    return *this;
  }

  static HtmlBuilder Create(std::string root_name) { return {root_name}; }

  // Very strong suggestion to the customer to use the Builder is to have a Create function.
  HtmlElement Build() { return root; }

  operator HtmlElement() const { return root; }

  std::string str() const { return root.str(); }
};
}  // namespace good

}  // namespace builder_pattern
}  // namespace creational

// TEST---------------------------------------------------------------------------------------------------------------|

#include "gtest/gtest.h"

namespace {

using namespace creational::builder_pattern;

TEST(BuilderPatternTest, NoUseOfBuilder) {
  std::cout << "First function's output:\n";
  bad::FunctionWithoutBuilder();
  std::cout << std::endl;

  std::cout << "Second function's output:\n";
  bad::AnotherFunctionWithoutBuilder();
}

TEST(BuilderPatternTest, StructureUsingBuilderPattern) {
  good::HtmlBuilder builder{"ul"};
  builder.AddChild("li", "hello").AddChild("li", "world");
  std::cout << builder.str() << std::endl;

  good::HtmlBuilder builder2 = good::HtmlBuilder::Create("ul").AddChild("", "");
  std::cout << builder2.str() << std::endl;

  // Valid only thanks to the operator() overload.
  good::HtmlElement elem = good::HtmlBuilder::Create("ul").AddChild("", "");
  std::cout << elem.str() << std::endl;

  // Usage of the Build() function
  good::HtmlElement builded_elem = good::HtmlBuilder("ul")
                                       .AddChild("li", "What do you think about the Builder Pattern?")
                                       .AddChild("li", "The Build Pattern rocks!")
                                       .AddChild("li", "Correct!")
                                       .Build();
  std::cout << builded_elem.str() << std::endl;

  // good::HtmlElement e; // Not available! All constructors are private therefore you have to use the builder!
}

}  // namespace
