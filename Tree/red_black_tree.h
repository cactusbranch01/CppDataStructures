// Created by Ben Roberts 2024

#pragma once

#include <cassert>  // For std::assert
#include <cstddef>  // For size_t

template <typename ValueType> class RedBlackTree {
private:
  enum Color { RED, BLACK };

  struct Node {
    ValueType value;
    Color color;
    Node* left;
    Node* right;
    Node* parent;

    explicit Node(const ValueType& val)
        : value(val), color(RED), left(nullptr), right(nullptr),
          parent(nullptr) {}
  };

  Node* root_;
  size_t size_;

  void rotateLeft(Node* x) {
    Node* y = x->right;
    x->right = y->left;
    if (y->left) {
      y->left->parent = x;
    }
    y->parent = x->parent;
    if (!x->parent) {
      root_ = y;
    } else if (x == x->parent->left) {
      x->parent->left = y;
    } else {
      x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
  }

  void rotateRight(Node* x) {
    Node* y = x->left;
    x->left = y->right;
    if (y->right) {
      y->right->parent = x;
    }
    y->parent = x->parent;
    if (!x->parent) {
      root_ = y;
    } else if (x == x->parent->right) {
      x->parent->right = y;
    } else {
      x->parent->left = y;
    }
    y->right = x;
    x->parent = y;
  }

  // Restores the red-black properties after inserting the red node.
  void insertFixup(Node* node) {
    while (node->parent && node->parent->color == RED) {
      Node* parent = node->parent;
      // Grandparent exists because a red parent can never be the root
      Node* grandparent = parent->parent;
      if (parent == grandparent->left) {
        Node* uncle = grandparent->right;
        if (uncle && uncle->color == RED) {
          // Red uncle: recolor and continue from the grandparent
          parent->color = BLACK;
          uncle->color = BLACK;
          grandparent->color = RED;
          node = grandparent;
        } else {
          if (node == parent->right) {
            // Left-right case: rotate into the left-left case
            node = parent;
            rotateLeft(node);
            parent = node->parent;
          }
          parent->color = BLACK;
          grandparent->color = RED;
          rotateRight(grandparent);
        }
      } else {
        Node* uncle = grandparent->left;
        if (uncle && uncle->color == RED) {
          parent->color = BLACK;
          uncle->color = BLACK;
          grandparent->color = RED;
          node = grandparent;
        } else {
          if (node == parent->left) {
            node = parent;
            rotateRight(node);
            parent = node->parent;
          }
          parent->color = BLACK;
          grandparent->color = RED;
          rotateLeft(grandparent);
        }
      }
    }
    root_->color = BLACK;
  }

  // Replaces the subtree rooted at u with the subtree rooted at v.
  void transplant(Node* u, Node* v) {
    if (!u->parent) {
      root_ = v;
    } else if (u == u->parent->left) {
      u->parent->left = v;
    } else {
      u->parent->right = v;
    }
    if (v) {
      v->parent = u->parent;
    }
  }

  Node* minimum(Node* node) const {
    while (node->left) {
      node = node->left;
    }
    return node;
  }

  // Restores the red-black properties after removing a black node. x is
  // the node carrying the extra black (may be null), parent is its parent.
  void removeFixup(Node* x, Node* parent) {
    while (x != root_ && (!x || x->color == BLACK)) {
      if (x == parent->left) {
        // The sibling is non-null, otherwise the black heights of the
        // two subtrees of parent could not have matched before removal
        Node* sibling = parent->right;
        if (sibling->color == RED) {
          sibling->color = BLACK;
          parent->color = RED;
          rotateLeft(parent);
          sibling = parent->right;
        }
        if ((!sibling->left || sibling->left->color == BLACK) &&
            (!sibling->right || sibling->right->color == BLACK)) {
          sibling->color = RED;
          x = parent;
          parent = x->parent;
        } else {
          if (!sibling->right || sibling->right->color == BLACK) {
            if (sibling->left) {
              sibling->left->color = BLACK;
            }
            sibling->color = RED;
            rotateRight(sibling);
            sibling = parent->right;
          }
          sibling->color = parent->color;
          parent->color = BLACK;
          if (sibling->right) {
            sibling->right->color = BLACK;
          }
          rotateLeft(parent);
          x = root_;
        }
      } else {
        Node* sibling = parent->left;
        if (sibling->color == RED) {
          sibling->color = BLACK;
          parent->color = RED;
          rotateRight(parent);
          sibling = parent->left;
        }
        if ((!sibling->left || sibling->left->color == BLACK) &&
            (!sibling->right || sibling->right->color == BLACK)) {
          sibling->color = RED;
          x = parent;
          parent = x->parent;
        } else {
          if (!sibling->left || sibling->left->color == BLACK) {
            if (sibling->right) {
              sibling->right->color = BLACK;
            }
            sibling->color = RED;
            rotateLeft(sibling);
            sibling = parent->left;
          }
          sibling->color = parent->color;
          parent->color = BLACK;
          if (sibling->left) {
            sibling->left->color = BLACK;
          }
          rotateRight(parent);
          x = root_;
        }
      }
    }
    if (x) {
      x->color = BLACK;
    }
  }

  // Recursively deep copies the subtree rooted at node. Recursion depth
  // is bounded by the red-black height guarantee of 2*log2(n + 1).
  Node* copySubtree(const Node* node, Node* parent) {
    if (!node) {
      return nullptr;
    }
    Node* new_node = new Node(node->value);
    new_node->color = node->color;
    new_node->parent = parent;
    new_node->left = copySubtree(node->left, new_node);
    new_node->right = copySubtree(node->right, new_node);
    return new_node;
  }

  // Recursively deletes every node in the subtree rooted at node.
  void clearSubtree(Node* node) {
    if (!node) {
      return;
    }
    clearSubtree(node->left);
    clearSubtree(node->right);
    delete node;
  }

  // Returns the black height of the subtree if it satisfies the red-black
  // and ordering properties, or -1 if any property is violated.
  int validateSubtree(const Node* node) const {
    if (!node) {
      return 1;
    }
    if (node->color == RED &&
        ((node->left && node->left->color == RED) ||
         (node->right && node->right->color == RED))) {
      return -1;
    }
    if (node->left && !(node->left->value < node->value)) {
      return -1;
    }
    if (node->right && !(node->value < node->right->value)) {
      return -1;
    }
    int leftHeight = validateSubtree(node->left);
    int rightHeight = validateSubtree(node->right);
    if (leftHeight == -1 || rightHeight == -1 || leftHeight != rightHeight) {
      return -1;
    }
    return leftHeight + (node->color == BLACK ? 1 : 0);
  }

public:
  RedBlackTree() : root_(nullptr), size_(0) {}

  // Rule of 3: destructor, copy constructor, copy assignment
  ~RedBlackTree() { clear(); }

  // Copy constructor
  RedBlackTree(const RedBlackTree& other)
      : root_(copySubtree(other.root_, nullptr)), size_(other.size_) {}

  // Copy assignment
  RedBlackTree& operator=(const RedBlackTree& other) {
    if (this != &other) {
      clear();
      root_ = copySubtree(other.root_, nullptr);
      size_ = other.size_;
    }
    return *this;
  }

  void insert(const ValueType& value) {
    Node* parent = nullptr;
    Node* current = root_;
    while (current) {
      parent = current;
      if (value < current->value) {
        current = current->left;
      } else if (current->value < value) {
        current = current->right;
      } else {
        return; // Ignore duplicates
      }
    }
    Node* node = new Node(value);
    node->parent = parent;
    if (!parent) {
      root_ = node;
    } else if (value < parent->value) {
      parent->left = node;
    } else {
      parent->right = node;
    }
    ++size_;
    insertFixup(node);
  }

  void remove(const ValueType& value) {
    Node* z = root_;
    while (z) {
      if (value < z->value) {
        z = z->left;
      } else if (z->value < value) {
        z = z->right;
      } else {
        break;
      }
    }
    if (!z) {
      return;
    }

    Node* y = z;
    Color yOriginalColor = y->color;
    Node* x = nullptr;
    Node* xParent = nullptr;

    if (!z->left) {
      x = z->right;
      xParent = z->parent;
      transplant(z, z->right);
    } else if (!z->right) {
      x = z->left;
      xParent = z->parent;
      transplant(z, z->left);
    } else {
      // Two children: splice out the in-order successor and move it
      // into z's position, keeping z's color
      y = minimum(z->right);
      yOriginalColor = y->color;
      x = y->right;
      if (y->parent == z) {
        xParent = y;
      } else {
        xParent = y->parent;
        transplant(y, y->right);
        y->right = z->right;
        y->right->parent = y;
      }
      transplant(z, y);
      y->left = z->left;
      y->left->parent = y;
      y->color = z->color;
    }
    delete z;
    --size_;
    if (yOriginalColor == BLACK) {
      removeFixup(x, xParent);
    }
  }

  ValueType* find(const ValueType& value) {
    Node* current = root_;
    while (current) {
      if (value < current->value) {
        current = current->left;
      } else if (current->value < value) {
        current = current->right;
      } else {
        return &current->value;
      }
    }
    return nullptr;
  }

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

  // Returns true if the tree satisfies every red-black property.
  bool isValid() const {
    if (root_ && root_->color == RED) {
      return false;
    }
    return validateSubtree(root_) != -1;
  }

  void clear() {
    clearSubtree(root_);
    root_ = nullptr;
    size_ = 0;
  }

  size_t size() const { return size_; }

  bool empty() const { return size_ == 0; }
};
