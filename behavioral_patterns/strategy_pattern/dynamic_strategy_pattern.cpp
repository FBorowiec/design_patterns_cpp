/**
 * INTENT:
 * System behavior partially specified at runtime.
 * MOTIVATION:
 * Many algorithms can be decomposed into higher- and lower-level parts ex:
 *  Making tea can be decomposed:
 *  - Boil water, pour into cup
 *  - Tea specific things (teabag into water)
 *  The high-level algorithm can ten be reused for making another beverage.
 *
 * The strategy design pattern enables the exact behavior of a system to be selected
 * either at run-time (dynamic) or compile-time (static).
 * Also know as the Policy design patterns.
 *
 * Steps:
 *  - Define an algorithm at a high level
 *  - Define the interface you expect each strategy to follow
 *  - Provide for either dynamic or static composition of strategy in the overall algorithm
 */
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

namespace behavioral {
namespace strategy_pattern {

enum class OutpuFormat {
  markdown,
  // * item1
  // * item2

  html
  // <ul>
  //  <li>item1</li>
  // </ul>
};

struct ListStrategy {
  virtual ~ListStrategy() = default;
  virtual void Start(std::ostringstream& oss) { oss << ""; }
  virtual void End(std::ostringstream& oss) { oss << ""; }
  virtual void AddListItem(std::ostringstream& oss, const std::string& item) = 0;
};

struct MarkdownStrategy : public ListStrategy {
  void AddListItem(std::ostringstream& oss, const std::string& item) override { oss << " * " << item << "\n"; }
};

struct HtmlStrategy : public ListStrategy {
  void Start(std::ostringstream& oss) override { oss << "<ul>\n"; }

  void AddListItem(std::ostringstream& oss, const std::string& item) override {
    oss << "  <li>" << item << "</li>" << std::endl;
  }

  void End(std::ostringstream& oss) override { oss << "</ul>\n"; }
};

struct TextProcessor {
 public:
  void Clear() {
    oss_.str("");
    oss_.clear();
  }

  void AppendList(const std::vector<std::string>& items) {
    list_strategy_->Start(oss_);
    for (auto& item : items) {
      list_strategy_->AddListItem(oss_, item);
    }
    list_strategy_->End(oss_);
  }

  void SetOutputFormat(const OutpuFormat& format) {
    switch (format) {
      case OutpuFormat::markdown:
        list_strategy_ = std::make_unique<MarkdownStrategy>();
        break;
      case OutpuFormat::html:
        list_strategy_ = std::make_unique<HtmlStrategy>();
        break;
    }
  }

  std::string str() const { return oss_.str(); }

 private:
  std::ostringstream oss_;
  std::unique_ptr<ListStrategy> list_strategy_;
};

}  // namespace strategy_pattern
}  // namespace behavioral

// TEST---------------------------------------------------------------------------------------------------------------|

#include "gtest/gtest.h"

namespace {

using namespace behavioral::strategy_pattern;

TEST(StrategyPatternTest, UsageOfTheStrategyPattern) {
  std::vector<std::string> items{"foo", "bar", "baz"};

  TextProcessor tp;
  tp.SetOutputFormat(OutpuFormat::markdown);
  tp.AppendList(items);

  std::cout << tp.str() << std::endl;

  tp.Clear();
  tp.SetOutputFormat(OutpuFormat::html);
  tp.AppendList(items);
  std::cout << tp.str() << std::endl;
}

}  // namespace
