/**
 * Given the following definition of a Node<T>, please implement preorder traversal that retruns a sequence of Ts.
 */
#include <iostream>
#include <vector>

namespace behavioral {
namespace iterator_pattern_exercise {

template <typename T>
struct Node {
  Node(T value) : value_(value) {}
  Node(T value, Node<T> *left, Node<T> *right) : value_(value), left_(left), right_(right) {
    left_->parent_ = right_->parent_ = this;
  }

  // traverse the node and its children preorder
  // and put all the results into `result`
  void preorder_traversal_impl(Node<T> *current, std::vector<Node<T> *> &result) {
    result.push_back(current);
    if (current->left_) {
      preorder_traversal_impl(current->left_, result);
    }
    if (current->right_) {
      preorder_traversal_impl(current->right_, result);
    }
  }
  // traverse the node and its children preorder
  // and put all the results into `result`
  void preorder_traversal(std::vector<Node<T> *> &result) { preorder_traversal_impl(this, result); }

  T value_;
  Node *left_{nullptr}, *right_{nullptr}, *parent_{nullptr};
};

}  // namespace iterator_pattern_exercise
}  // namespace behavioral

// TEST---------------------------------------------------------------------------------------------------------------|
#include <ostream>
#include "gtest/gtest.h"

namespace {

using namespace behavioral::iterator_pattern_exercise;

TEST(IteratorPatternExerciseTest, SimpleTest) {
  Node<char> c{'c'};
  Node<char> d{'d'};
  Node<char> e{'e'};
  Node<char> b{'b', &c, &d};
  Node<char> a{'a', &b, &e};

  std::vector<Node<char> *> result;
  a.preorder_traversal(result);

  std::ostringstream oss;
  for (auto n : result) oss << n->value_;
  ASSERT_EQ("abcde", oss.str());
}

}  // namespace
