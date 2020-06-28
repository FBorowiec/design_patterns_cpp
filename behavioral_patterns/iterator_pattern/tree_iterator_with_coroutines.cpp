#include <experimental/coroutine>
#include <experimental/generator>
#include <iostream>
#include <string>

namespace behavioral {
namespace iterator_pattern {

/**
 *        A
 *      /   \
 *     B     C
 */
template <typename T>
struct BinaryTree;

template <typename T>
struct Node {
  T value_ = T();
  Node<T>*left_{nullptr}, *right_{nullptr}, *parent_{nullptr};
  BinaryTree<T>* tree_{nullptr};

  Node(T value) : value_(value) {}

  Node(T value, Node<T>* left, Node<T>* right) : value_(value), left_(left), right_(right) {
    this->right_->tree_ = this->left_->tree_ = tree_;
    this->right_->parent_ = this->left_->parent_ = this;
  }

  void SetTree(BinaryTree<T>* t) {
    tree_ = t;
    if (left_) left_->SetTree(t);
    if (right_) right_->SetTree(t);
  }

  ~Node() {
    if (left_) delete left_;
    if (right_) delete right_;
  }
};

template <typename T>
struct BinaryTree {
  Node<T>* root_{nullptr};

  BinaryTree(Node<T>* root) : root_(root) { root->SetTree(this); }

  ~BinaryTree() {
    if (root_) delete root_;
  }

  // Iterator for Binary Tree
  template <typename U>
  struct PreOrderIterator {
    Node<U>* current_;
    PreOrderIterator(Node<U>* current) : current_(current) {}

    bool operator!=(const PreOrderIterator<U>& other) { return current_ != other.current_; }

    PreOrderIterator<U>& operator++() {
      if (current_->right_) {
        current_ = current_->right_;
        while (current_->left_) {
          current_ = current_->left_;
        }
      } else {
        Node<T>* p = current_->parent_;
        while (p && current_ == p->right_) {
          current_ = p;
          p = p->parent_;
        }
        current_ = p;
      }
      return *this;
    }

    Node<U>& operator*() { return *current_; }
  };  // PreOrderIterator

  typedef PreOrderIterator<T> iterator;
  iterator begin() {
    Node<T>* n = root_;
    if (n) {
      while (n->left_) {
        n = n->left_;
      }
    }
    return iterator{nullptr};
  }

  iterator end() { return iterator{nullptr}; }

  // RECURSE TRAVERSAL
  class PreOrderTraversal {
    BinaryTree& tree_;

   public:
    PreOrderTraversal(BinaryTree& tree) : tree_(tree) {}
    iterator begin() { return tree_.begin(); }
    iterator end() { return tree_.end(); }
  } pre_order;

  experimental::generator<Node<T>*> PostOrder() { return PostOrderImpl(root_); }

 private:
  experimental::generator<Node<T>*> PostOrderImpl(Node<T>* node) {
    if (node) {
      for (auto x : PostOrderImpl(node->left_)) co_yield x;
      for (auto y : PostOrderImpl(node->right_)) co_yield y;
      co_yield node;
    }
  }
};

}  // namespace iterator_pattern
}  // namespace behavioral

// TEST---------------------------------------------------------------------------------------------------------------|

#include "gtest/gtest.h"

namespace {

using namespace behavioral::iterator_pattern;

TEST(IteratorPatternTest, IteratorsInTheStandardTemplateLibrary) {
  /**
   *            Me
   *           /  \
   *      Mother   Father
   *      /   \
   *    m'm   m'f
   */
  BinaryTree<std::string> family{
      new Node<std::string>{"Me",
                            new Node<std::string>{"Mother", new Node<std::string>{"Mother's mother"},
                                                  new Node<std::string>{"Mother's father"}},
                            new Node<std::string>{"Father"}}};

  for (const auto& it : family.pre_order) {
    // ...
  }

  for (const auto& it : family.PostOrder()) {
    std::cout << it->value_ << std::endl;
  }
}

}  // namespace
