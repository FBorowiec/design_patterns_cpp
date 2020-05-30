/**
 * The system should be open to extensions (for example with inheritance) but closed to modifications
 */
#include <string>
#include <vector>

namespace solid_principles {
namespace open_closed_principle {

enum class Color { red, green, blue };
enum class Size { small, medium, large };

struct Product {
  std::string name{};
  Color color{};
  Size size{};
};

namespace bad {
struct ProductFilter {
  // The solution is only as good as long there is only one or two filters.
  std::vector<Product*> ByColor(std::vector<Product*> products, Color color) {
    std::vector<Product*> products_by_color{};
    for (auto& p : products)
      if (p->color == color) products_by_color.push_back(p);
    return products_by_color;
  }

  // BAD! Now every new filter requires a new chunk of copied code do perform a similar action.
  std::vector<Product*> BySize(std::vector<Product*> products, Size size) {
    std::vector<Product*> products_by_size{};
    for (auto& p : products)
      if (p->size == size) products_by_size.push_back(p);
    return products_by_size;
  }

  // The solution doesn't scale at all. Any new combination makes the codebase explode.
  std::vector<Product*> BySizeAndColor(std::vector<Product*> products, Size size, Color color) {
    std::vector<Product*> products_by_size_and_color{};
    for (auto& p : products)
      if (p->size == size && p->color == color) products_by_size_and_color.push_back(p);
    return products_by_size_and_color;
  }
};
}  // namespace bad

namespace good {
// The good approach envolves using an interface for both product and specification
template <typename T>
struct Specification {
  virtual ~Specification() = default;
  virtual bool IsSatisfied(T* item) const = 0;
};

template <typename T>
struct Filter {
  virtual std::vector<T*> FilterWithSpec(std::vector<T*> items, Specification<T>& spec) = 0;
};

struct BetterFilter : public Filter<Product> {
  std::vector<Product*> FilterWithSpec(std::vector<Product*> items, Specification<Product>& spec) override {
    std::vector<Product*> filtered_items{};
    for (auto& item : items) {
      if (spec.IsSatisfied(item)) filtered_items.push_back(item);
    }
    return filtered_items;
  }
};

struct ColorSpecification : Specification<Product> {
  ColorSpecification(Color color) : color_(color) {}

  bool IsSatisfied(Product* item) const override { return item->color == color_; }

  Color color_{};
};

struct SizeSpecification : Specification<Product> {
  explicit SizeSpecification(Size size) : size_(size) {}

  bool IsSatisfied(Product* item) const override { return item->size == size_; }

  Size size_{};
};

// But what if we need to combine specifications? Here you use a combinator
template <typename T>
struct AndSpecification : Specification<T> {
  AndSpecification(Specification<T>& first, Specification<T>& second) : first_spec(first), second_spec(second) {}

  bool IsSatisfied(T* item) const override { return first_spec.IsSatisfied(item) && second_spec.IsSatisfied(item); }

  Specification<T>& first_spec{};
  Specification<T>& second_spec{};
};

}  // namespace good

}  // namespace open_closed_principle
}  // namespace solid_principles

// TEST---------------------------------------------------------------------------------------------------------------|

#include <iostream>
#include "gtest/gtest.h"

namespace {

using namespace solid_principles::open_closed_principle;

TEST(OpenClosedPrincipleTest, ExampleOfClassViolatingTheOCPrinciple) {
  Product apple{"Apple", Color::green, Size::small};
  Product tree{"Tree", Color::green, Size::large};
  Product house{"House", Color::blue, Size::large};

  std::vector<Product*> items{&apple, &tree, &house};
  bad::ProductFilter pf{};

  auto green_stuff = pf.ByColor(items, Color::green);
  for (auto& item : green_stuff) std::cout << item->name << " is green\n";

  auto large_stuff = pf.BySize(items, Size::large);
  for (auto& item : large_stuff) std::cout << item->name << " is large\n";

  auto green_and_large_stuff = pf.BySizeAndColor(items, Size::large, Color::green);
  for (auto& item : green_and_large_stuff) std::cout << item->name << " is green and large\n";
}

TEST(OpenClosedPrincipleTest, ExampleOfClassFollowingTheOCPrinciple) {
  Product apple{"Apple", Color::green, Size::small};
  Product tree{"Tree", Color::green, Size::large};
  Product house{"House", Color::blue, Size::large};

  std::vector<Product*> items{&apple, &tree, &house};
  good::BetterFilter bf{};
  good::ColorSpecification green(Color::green);

  for (auto& item : bf.FilterWithSpec(items, green)) std::cout << item->name << " is green\n";

  good::SizeSpecification large(Size::large);
  good::AndSpecification<Product> green_and_large(green, large);

  for (auto& item : bf.FilterWithSpec(items, green_and_large)) std::cout << item->name << " is green and large\n";
}

}  // namespace
