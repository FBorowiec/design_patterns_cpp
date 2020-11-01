/**
 * You are given a class called Sentence, which takes a string such as "hello world". You need to provide an interface
 * an interface such that the indexer (operator{}) returns a WordToken that can be used to capitalize a particular word
 * in the sentence.
 *
 * Typical use would be:
 *
 * Sentence sentence("hello world");
 * sentence[1].capitalize = true;
 * std::cout << sentence.str();  // prints "hello WORLD"
 */
#include <algorithm>
#include <cctype>
#include <iterator>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

namespace structural {
namespace flyweight_pattern_exercise {

struct Sentence {
  struct WordToken {
    bool capitalize;
  };

  WordToken& operator[](unsigned int index) {
    tokens_[index] = WordToken{};
    return tokens_[index];
  }

  Sentence(const std::string& text) {
    std::istringstream iss{text};
    sentence_ = std::vector<std::string>(std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>{});
  }

  std::string str() const {
    std::vector<std::string> ws;
    for (unsigned int i = 0; i < sentence_.size(); ++i) {
      std::string w = sentence_[i];
      auto t = tokens_.find(i);
      if (t != tokens_.end() && t->second.capitalize) {
        std::transform(w.begin(), w.end(), w.begin(), [](int c) -> int { return std::toupper(c); });
      }
      ws.push_back(w);
    }

    std::ostringstream oss;
    for (size_t i = 0; i < ws.size(); ++i) {
      oss << ws[i];
      if (i + 1 != ws.size()) oss << " ";
    }
    return oss.str();
  }

  std::vector<std::string> sentence_;
  std::unordered_map<unsigned int, WordToken> tokens_;
};

}  // namespace flyweight_pattern_exercise
}  // namespace structural

// TEST---------------------------------------------------------------------------------------------------------------|
#include "gtest/gtest.h"

namespace {

using namespace structural::flyweight_pattern_exercise;

TEST(FlyweightPatternExerciseTest, BaselineTest) {
  Sentence s{"alpha beta gamma"};
  s[0].capitalize = s[2].capitalize = false;
  s[1].capitalize = true;
  ASSERT_EQ("alpha BETA gamma", s.str());
}

}  // namespace
