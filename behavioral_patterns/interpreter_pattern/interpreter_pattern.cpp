/**
 * INTENT:
 * How to write parsers.
 * MOTIVATION:
 * Textual input needs to be processed e.g.:
 *  - Turned into OOP structures
 *  - Programming languages compilers, interpreters and IDEs
 *  - HTML, XML and similar
 *  - Numeric expressions (3+4/5)
 *  - Regular expressions
 *
 * So the interpreter is about turning strings into OOP based structures in a complicated process.
 * It does so in two stages:
 * 1. Separating lexical tokens (lexing) : 3*(4+5) -> Lit[3] Star Lparen Lit[4] Plus Lit[5] Rparen
 * 2. Interpreting sequences of said tokens (parsing) ->
 *        MultiplicationExpression[Integer[3], AdditionExpression[Integer[4], Integer[5]]]
 */
#include <iostream>
#include <memory>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>

namespace behavioral {
namespace interpreter_pattern {

enum Type { integer, plus, minus, lparen, rparen };

struct Token {
 public:
  explicit Token(const Type type, const std::string& text) : type_(type), text_(text) {}

  friend std::ostream& operator<<(std::ostream& os, const Token& token) {
    os << "`" << token.text_ << "`";
    return os;
  }

  std::string GetText() const { return text_; }
  Type GetType() const { return type_; }

 private:
  Type type_;
  std::string text_;
};

// Lexing -----v
std::vector<Token> Lex(const std::string& input) {
  std::vector<Token> result{};

  for (unsigned int i = 0; i < input.size(); ++i) {
    switch (input[i]) {
      case '+':
        result.push_back(Token{Type::plus, "+"});
        break;
      case '-':
        result.push_back(Token{Type::minus, "-"});
        break;
      case '(':
        result.push_back(Token{Type::lparen, "("});
        break;
      case ')':
        result.push_back(Token{Type::rparen, ")"});
        break;
      default:
        std::ostringstream buffer;
        buffer << input[i];
        for (unsigned int j = i + 1; input.size(); j++) {
          if (isdigit(input[j])) {
            buffer << input[j];
            ++i;
          } else {
            result.push_back(Token{Type::integer, buffer.str()});
            break;
          }
        }
    }
  }
  return result;
}

// Parsing -----v
struct Element {
  virtual int Eval() const = 0;
};

struct Integer : public Element {
  int value_;

  Integer(int value) : value_(value) {}

  int Eval() const override { return value_; }
};

struct BinaryOperation : public Element {
  enum Type { addition, subtraction } type_;
  std::shared_ptr<Element> lhs, rhs;

  int Eval() const override {
    auto left = lhs->Eval();
    auto right = rhs->Eval();
    if (type_ == addition) return left + right;
    return left - right;
  }
};

std::shared_ptr<Element> Parse(const std::vector<Token>& tokens) {
  auto result = std::make_unique<BinaryOperation>();
  bool have_lhs{false};

  for (unsigned int i = 0; i < tokens.size(); ++i) {
    auto token = tokens[i];
    switch (token.GetType()) {
      case Type::integer: {
        int value = std::stoi(token.GetText());
        auto integer = std::make_shared<Integer>(value);
        if (!have_lhs) {
          result->lhs = integer;
          have_lhs = true;
        } else
          result->rhs = integer;
        break;
      }
      case Type::plus:
        result->type_ = BinaryOperation::addition;
        break;
      case Type::minus:
        result->type_ = BinaryOperation::subtraction;
        break;
      case Type::lparen: {
        unsigned int j = i;
        for (; j < tokens.size(); ++j)
          if (tokens[j].GetType() == Type::rparen) break;  // found it!

        std::vector<Token> subexpression(&tokens[i + 1], &tokens[j]);
        auto element = Parse(subexpression);
        if (!have_lhs) {
          result->lhs = element;
          have_lhs = true;
        } else
          result->rhs = element;
        i = j;  // advance
      } break;
      default:
        break;
    }
  }
  return result;
}

}  // namespace interpreter_pattern
}  // namespace behavioral

// TEST---------------------------------------------------------------------------------------------------------------|

#include "gtest/gtest.h"

namespace {

using namespace behavioral::interpreter_pattern;

TEST(InterpreterPatternTest, UsageOfTheInterpreterPattern) {
  std::string input{"(13-4)-(12+1)"};
  auto tokens = Lex(input);

  for (auto& t : tokens) std::cout << t << "  ";
  std::cout << std::endl;

  try {
    auto parsed = Parse(tokens);
    std::cout << input << " = " << parsed->Eval() << std::endl;
  } catch (const std::exception& e) {
    std::cout << e.what() << std::endl;
  }
}

}  // namespace
