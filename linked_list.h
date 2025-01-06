//
// Created by Ben Roberts on 2024.
//

#pragma once

#include <cassert>  // For std::assert
#include <cstddef>  // For std::ptrdiff_t
#include <iterator> // For std::forward_iterator_tag

template <typename ValueType> class LinkedList {
private:
  struct Node {
    ValueType value;
    Node *next;
    Node *prev;

    explicit Node(const ValueType &val)
        : value(val), next(nullptr), prev(nullptr) {}
  };

  Node *head_;
  Node *tail_;
  size_t size_;

  void clear() {
    Node *current = head_;
    while (current != nullptr) {
      Node *tmp = current;
      current = current->next;
      delete tmp;
    }
    head_ = tail_ = nullptr;
    size_ = 0;
  }

public:
  LinkedList() : head_(nullptr), tail_(nullptr), size_(0) {}

  // Rule of 5: destructor, copy constructor, copy assignment, move constructor,
  // move assignment
  ~LinkedList() { clear(); }

  // Copy constructor
  LinkedList(const LinkedList &other)
      : head_(nullptr), tail_(nullptr), size_(0) {
    for (const auto &value : other) {
      pushBack(value);
    }
  }

  // Copy assignment
  LinkedList &operator=(const LinkedList &other) noexcept {
    if (this != &other) {
      clear();
      for (const auto &value : other) {
        pushBack(value);
      }
    }
    return *this;
  }

  // Move constructor
  LinkedList(const LinkedList &&other) noexcept
      : head_(other.head_), tail_(other.tail_), size_(other.size_) {
    // this != other guaranteed by the fact that the rvalue ref cannot be the
    // same ref as this in std::move
    other.head_ = nullptr;
    other.tail_ = nullptr;
    other.size_ = 0;
  }

  // Move assignment
  LinkedList &operator=(LinkedList &&other) noexcept {
    if (this != &other) {
      clear();
      // Transfer pointers from other
      head_ = other.head_;
      tail_ = other.tail_;
      size_ = other.size_;

      // Release other ownership
      other.head_ = nullptr;
      other.tail_ = nullptr;
      other.size_ = 0;
    }
    return *this;
  }

  void pushFront(const ValueType &value) {
    Node *new_node = new Node(value);
    if (!head_) {
      head_ = tail_ = new_node;
    } else {
      new_node->next = head_;
      head_->prev = new_node;
      head_ = new_node;
    }
    ++size_;
  }

  void pushBack(const ValueType &value) {
    Node *new_node = new Node(value);
    if (!tail_) {
      head_ = tail_ = new_node;
    } else {
      tail_->next = new_node;
      new_node->prev = tail_;
      tail_ = new_node;
    }
    ++size_;
  }

  void popFront() {
    assert(!empty());
    auto temp = head_;
    head_ = head_->next;
    if (head_) {
      head_->prev = nullptr;
    } else {
      tail_ = nullptr;
    }
    delete temp;
    --size_;
  }

  void popBack() {
    assert(!empty());
    auto temp = tail_;
    tail_ = tail_->prev;
    if (tail_) {
      tail_->next = nullptr;
    } else {
      head_ = nullptr;
    }
    delete temp;
    --size_;
  }

  ValueType &front() {
    assert(!empty());
    return head_->value;
  }

  const ValueType &front() const {
    assert(!empty());
    return head_->value;
  }

  ValueType &back() {
    assert(!empty());
    return tail_->value;
  }

  const ValueType &back() const {
    assert(!empty());
    return tail_->value;
  }

  size_t size() const { return size_; }

  bool empty() const { return size_ == 0; }

  class Iterator {
  private:
    Node *current_;

  public:
    using iterator_category = std::forward_iterator_tag;
    using value_type = ValueType;
    using difference_type = std::ptrdiff_t;
    using pointer = ValueType *;
    using reference = ValueType &;

    explicit Iterator(Node *node) : current_(node) {}

    reference operator*() const { return current_->value; }
    pointer operator->() const { return &(current_->value); }

    // Prefix increment
    Iterator &operator++() {
      if (current_) {
        current_ = current_->next;
      }
      return *this;
    }

    // Postfix increment
    Iterator operator++(int) {
      Iterator temp = *this;
      ++(*this);
      return temp;
    }

    bool operator==(const Iterator &other) const {
      return current_ == other.current_;
    }
    bool operator!=(const Iterator &other) const {
      return current_ != other.current_;
    }
  };

  // Returns an iterator to the first element of the list.
  Iterator begin() const { return Iterator(head_); }
  // Returns an iterator to one past the last element of the list.
  Iterator end() const { return Iterator(nullptr); }
};
