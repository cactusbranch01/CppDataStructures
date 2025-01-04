//
// Created by Ben Roberts on 2024.
//

#pragma once

#include <cstddef>   // For std::ptrdiff_t
#include <iterator>  // For std::forward_iterator_tag
#include <cassert>   // For std::assert

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

  ~LinkedList() { clear(); }

  LinkedList(const LinkedList &other)
      : head_(nullptr), tail_(nullptr), size_(0) {
    for (const auto &value : other) {
      pushBack(value);
    }
  }

  LinkedList &operator=(const LinkedList &other) {
    if (this != &other) {
      clear();
      for (const auto &value : other) {
        pushBack(value);
      }
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
    assert(!isEmpty());
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
    assert(!isEmpty());
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
    assert(!isEmpty());
    return head_->value;
  }

  const ValueType &front() const {
    assert(!isEmpty());
    return head_->value;
  }

  ValueType &back() {
    assert(!isEmpty());
    return tail_->value;
  }

  const ValueType &back() const {
    assert(!isEmpty());
    return tail_->value;
  }

  size_t size() const { return size_; }

  bool isEmpty() const { return size_ == 0; }

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
