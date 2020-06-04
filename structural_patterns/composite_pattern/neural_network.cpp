#include <iostream>
#include <vector>

namespace structural {
namespace composite_pattern {

struct Neuron {
  std::vector<Neuron*> in, out;
  unsigned int id;

  Neuron() {
    static unsigned int id_{1};
    this->id = id_++;
  }

  /**
   * A single object can therefore masquerade as a collection:
   *  Foo* begin() { return this; }
   *  Foo* end() { return this+1; }
   */
  Neuron* begin() { return this; }
  Neuron* end() { return this + 1; }

  void ConnectTo(Neuron& other) {
    out.push_back(&other);
    other.in.push_back(this);
  }

  friend std::ostream& operator<<(std::ostream& os, const Neuron& obj) {
    for (Neuron* n : obj.in) {
      os << " " << n->id << " "
         << "\t-->\t[" << obj.id << "]" << std::endl;
    }
    for (Neuron* n : obj.out) {
      os << "[" << obj.id << "]\t-->\t"
         << " " << n->id << " " << std::endl;
    }
    return os;
  }
};

template <typename Self>
struct SomeNeurons {
  template <typename T>
  void ConnectTo(T& other) {
    for (Neuron& from : *static_cast<Self*>(this)) {
      for (Neuron& to : other) {
        from.out.push_back(&to);
        to.in.push_back(&from);
      }
    }
  }
};

// Inheriting from stl standard types is not recommended as they do not have virtual destructors
struct NeuronLayer : public std::vector<Neuron>, SomeNeurons<NeuronLayer> {
  NeuronLayer(int count) {
    while (count-- > 0) emplace_back(Neuron{});
  }

  friend std::ostream& operator<<(std::ostream& os, const NeuronLayer& obj) {
    for (const auto& n : obj) os << n;
    return os;
  }
};

}  // namespace composite_pattern
}  // namespace structural

// TEST---------------------------------------------------------------------------------------------------------------|

#include "gtest/gtest.h"

namespace {

using namespace structural::composite_pattern;

TEST(CompositePatternNNTest, UsageOfTheCompositePattern) {
  Neuron n1, n2;
  n1.ConnectTo(n2);
  std::cout << n1 << n2 << std::endl;
}

TEST(CompositePatternNNTest, UsageOfTheCompositePatternForNeuronLayers) {
  Neuron n1, n2;
  n1.ConnectTo(n2);

  NeuronLayer layer1{5};
  Neuron n3;
  layer1.ConnectTo(n3);

  std::cout << "Neuron " << n3.id << std::endl << n3 << std::endl;

  NeuronLayer layer2{2}, layer3{3};
  layer2.ConnectTo(layer3);

  std::cout << "Layer 2 " << std::endl << layer2;
  std::cout << "Layer 3 " << std::endl << layer3;
}

}  // namespace
