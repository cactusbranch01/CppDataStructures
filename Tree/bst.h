// Created by Ben Roberts 2024

#pragma once

#include <cassert>  // For std::assert
#include <cstddef>  // For size_t

template <typename ValueType> class BST {
private:
  struct Node {
    ValueType value;
    Node* left;
    Node* right;

    explicit Node(const ValueType& val)
        : value(val), left(nullptr), right(nullptr) {}
  };

  Node* root_;
  size_t size_;

  // Recursively deep copies the subtree rooted at node.
  Node* copySubtree(const Node* node) {
    if (!node) {
      return nullptr;
    }
    Node* new_node = new Node(node->value);
    new_node->left = copySubtree(node->left);
    new_node->right = copySubtree(node->right);
    return new_node;
  }

  // Inserts value into the subtree rooted at node, ignoring duplicates.
  Node* insertHelper(Node* node, const ValueType& value) {
    if (!node) {
      ++size_;
      return new Node(value);
    }
    if (value < node->value) {
      node->left = insertHelper(node->left, value);
    } else if (node->value < value) {
      node->right = insertHelper(node->right, value);
    }
    return node;
  }

  // Removes value from the subtree rooted at node if present.
  Node* removeHelper(Node* node, const ValueType& value) {
    if (!node) {
      return nullptr;
    }
    if (value < node->value) {
      node->left = removeHelper(node->left, value);
    } else if (node->value < value) {
      node->right = removeHelper(node->right, value);
    } else if (!node->left) {
      Node* right = node->right;
      delete node;
      --size_;
      return right;
    } else if (!node->right) {
      Node* left = node->left;
      delete node;
      --size_;
      return left;
    } else {
      // Two children: replace with the in-order successor, then remove
      // the successor from the right subtree
      Node* successor = node->right;
      while (successor->left) {
        successor = successor->left;
      }
      node->value = successor->value;
      node->right = removeHelper(node->right, successor->value);
    }
    return node;
  }

public:
  BST() : root_(nullptr), size_(0) {}

  // Rule of 3: destructor, copy constructor, copy assignment
  ~BST() { clear(); }

  // Copy constructor
  BST(const BST& other) : root_(copySubtree(other.root_)), size_(other.size_) {}

  // Copy assignment
  BST& operator=(const BST& other) {
    if (this != &other) {
      clear();
      root_ = copySubtree(other.root_);
      size_ = other.size_;
    }
    return *this;
  }

  void insert(const ValueType& value) { root_ = insertHelper(root_, value); }

  void remove(const ValueType& value) { root_ = removeHelper(root_, value); }

  bool contains(const ValueType& value) const {
    const Node* current = root_;
    while (current) {
      if (value < current->value) {
        current = current->left;
      } else if (current->value < value) {
        current = current->right;
      } else {
        return true;
      }
    }
    return false;
  }

  const ValueType& min() const {
    assert(!empty());
    const Node* current = root_;
    while (current->left) {
      current = current->left;
    }
    return current->value;
  }

  const ValueType& max() const {
    assert(!empty());
    const Node* current = root_;
    while (current->right) {
      current = current->right;
    }
    return current->value;
  }

  // Iteratively deletes every node using right rotations so that
  // destroying a degenerate (linked-list shaped) tree cannot overflow
  // the call stack.
  void clear() {
    Node* current = root_;
    while (current) {
      if (current->left) {
        Node* left = current->left;
        current->left = left->right;
        left->right = current;
        current = left;
      } else {
        Node* temp = current;
        current = current->right;
        delete temp;
      }
    }
    root_ = nullptr;
    size_ = 0;
  }

  size_t size() const { return size_; }

  bool empty() const { return size_ == 0; }
};
