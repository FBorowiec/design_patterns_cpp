/**
 * Implement the Builder design pattern for rendering chunks of code.
 * Sample use of the builder you ar asked to create:
 * auto cb = CodeBuilder{"Person"}.add_field("name", "string").add_field("age", "int");
 * cout << cb;
 *
 * The expected output of the above code is:
 * class Person
 * {
 *   string name;
 *   int age;
 * };
 */
#include <ostream>
#include <string>
#include <vector>
using namespace std;

namespace creational {
namespace builder_pattern_exercise {

struct Field {
  std::string name_, type_;

  Field(const std::string& name, const std::string& type) : name_{name}, type_{type} {}

  friend ostream& operator<<(ostream& os, const Field& obj) { return os << obj.type_ << " " << obj.name_ << ";"; }
};

struct Class {
  std::string name_;
  std::vector<Field> fields;

  friend ostream& operator<<(ostream& os, const Class& obj) {
    os << "class " << obj.name_ << "\n{\n";
    for (auto&& field : obj.fields) {
      os << "  " << field << "\n";
    }
    return os << "};\n";
  }
};

class CodeBuilder {
  Class the_class;

 public:
  CodeBuilder(const std::string& class_name_) { the_class.name_ = class_name_; }

  CodeBuilder& add_field(const std::string& name_, const std::string& type_) {
    the_class.fields.emplace_back(Field{name_, type_});
    return *this;
  }

  friend ostream& operator<<(ostream& os, const CodeBuilder& obj) { return os << obj.the_class; }
};

}  // namespace builder_pattern_exercise
}  // namespace creational

// TEST---------------------------------------------------------------------------------------------------------------|
#include <algorithm>
#include <cctype>
#include <locale>
#include <string>

#include "gtest/gtest.h"

namespace {
class Evaluate : public testing::Test {
 public:
  // trim from start (in place)
  static inline void ltrim(std::string& s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) { return !std::isspace(ch); }));
  }

  // trim from end (in place)
  static inline void rtrim(std::string& s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) { return !std::isspace(ch); }).base(), s.end());
  }

  // trim from both ends (in place)
  static inline void trim(std::string& s) {
    ltrim(s);
    rtrim(s);
  }

  // trim from start (copying)
  static inline std::string ltrim_copy(std::string s) {
    ltrim(s);
    return s;
  }

  // trim from end (copying)
  static inline std::string rtrim_copy(std::string s) {
    rtrim(s);
    return s;
  }
};

using namespace creational::builder_pattern_exercise;

TEST(CodeBuilderTest, EmptyTest) {
  CodeBuilder cb{"Foo"};
  ostringstream oss;
  oss << cb;
  auto printed = oss.str();
  Evaluate::trim(printed);
  ASSERT_EQ("class Foo\n{\n};", printed);
}

TEST(CodeBuilderTest, PersonTest) {
  auto cb = CodeBuilder{"Person"}.add_field("name", "string").add_field("age", "int");
  ostringstream oss;
  oss << cb;
  auto printed = oss.str();
  Evaluate::trim(printed);
  ASSERT_EQ("class Person\n{\n  string name;\n  int age;\n};", printed);
}
}  // namespace