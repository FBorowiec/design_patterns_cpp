#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

namespace behavioral {
namespace static_strategy_pattern {

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

template <typename LS>
struct TextProcessor {
 public:
  void Clear() {
    oss_.str("");
    oss_.clear();
  }

  void AppendList(const std::vector<std::string>& items) {
    list_strategy_.Start(oss_);
    for (auto& item : items) {
      list_strategy_.AddListItem(oss_, item);
    }
    list_strategy_.End(oss_);
  }

  std::string str() const { return oss_.str(); }

 private:
  std::ostringstream oss_;
  LS list_strategy_;
};

}  // namespace static_strategy_pattern
}  // namespace behavioral

// TEST---------------------------------------------------------------------------------------------------------------|

#include "gtest/gtest.h"

namespace {

using namespace behavioral::static_strategy_pattern;

TEST(StrategyPatternTest, UsageOfTheStrategyPattern) {
  std::vector<std::string> items{"foo", "bar", "baz"};

  TextProcessor<MarkdownStrategy> tp_md;
  tp_md.AppendList(items);
  std::cout << tp_md.str() << std::endl;

  TextProcessor<HtmlStrategy> tp_html;
  tp_html.AppendList(items);
  std::cout << tp_html.str() << std::endl;
}

}  // namespace
