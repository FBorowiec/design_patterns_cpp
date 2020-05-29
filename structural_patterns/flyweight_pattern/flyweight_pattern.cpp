/**
 * Space optimization.
 * MOTIVATION:
 *  - Avoid redundancy when storing data
 *  - Store data and pointers to that data
 *
 * A space optimization technique that lets us use less memory
 * by storing externally the data associated with similar objects.
 *
 * Store common data externally (e.g in a static map).
 * Define the idea of 'ranges' on homogeneous collections - store data related to those ranges.
 */
#include <memory>
#include <string>
#include <vector>

namespace structural {
namespace flyweight_pattern {

namespace bad {

class FormattedText {
 public:
  FormattedText(const std::string& text) : plain_text(text) { caps = new bool[plain_text.length()]; }

  ~FormattedText() { delete caps; }

  void Capitalize(int start, int end) {
    for (int i = start; i <= end; i++) {
      caps[i] = true;
    }
  }

  friend std::ostream& operator<<(std::ostream& os, const FormattedText& obj) {
    std::string s;
    for (long unsigned int i = 0; i < obj.plain_text.length(); i++) {
      char c = obj.plain_text[i];
      s += obj.caps[i] ? static_cast<char>(toupper(c)) : c;
    }
    return os << s;
  }

 private:
  std::string plain_text;
  bool* caps;
};

}  // namespace bad

namespace good {

class BetterFormattedText {
 public:
  BetterFormattedText(const std::string& plain_text) : plain_text_(plain_text) {}

  struct TextRange {
    int start{0}, end{0};
    bool capitalize{false};  // bold, italic

    bool Covers(int position) const { return position >= start && position <= end; }
  };

  TextRange& GetRange(int start, int end) {
    formatting.emplace_back(TextRange{start, end});
    return *formatting.rbegin();
  }

  friend std::ostream& operator<<(std::ostream& os, const BetterFormattedText& obj) {
    std::string s;
    for (int i = 0; i < static_cast<int>(obj.plain_text_.length()); i++) {
      auto c = static_cast<char>(obj.plain_text_[static_cast<long unsigned int>(i)]);
      for (const auto& rng : obj.formatting) {
        if (rng.Covers(static_cast<int>(i)) && rng.capitalize) c = static_cast<char>(toupper(c));
        s += c;
      }
    }
    return os << s;
  }

  std::string plain_text_;
  std::vector<TextRange> formatting;
};

}  // namespace good

}  // namespace flyweight_pattern
}  // namespace structural

// TEST---------------------------------------------------------------------------------------------------------------|

#include "gtest/gtest.h"

namespace {

using namespace structural::flyweight_pattern;

TEST(FlyweightPatternTest, NoUsageOfTheFlyweightPattern) {
  bad::FormattedText ft{"This is a brave new world"};
  ft.Capitalize(10, 15);
  std::cout << ft << std::endl;
}

TEST(FlyweightPatternTest, ProperUsageOfTheFlyweightPattern) {
  good::BetterFormattedText bft{"This is a brave new world"};
  bft.GetRange(10, 15).capitalize = true;
  std::cout << bft << std::endl;
}

}  // namespace
