// Created by Ben Roberts 2025

#pragma once

#include <cassert>  // For std::assert
#include <cstddef>  // For std::ptrdiff_t
#include <iterator> // For std::forward_iterator_tag

template <typename ValueType> class SingleLinkedList {
private:
  struct Node {
    ValueType value;
    Node* next;

    explicit Node(const ValueType& val) : value(val), next(nullptr) {}
  };

  Node* head_;
  Node* tail_;
  size_t size_;

  void clear() {
    Node* current = head_;
    while (current != nullptr) {
      Node* tmp = current;
      current = current->next;
      delete tmp;
    }
    head_ = tail_ = nullptr;
    size_ = 0;
  }

public:
  // Constructor
  SingleLinkedList() : head_(nullptr), tail_(nullptr), size_(0) {}

  // Destructor
  ~SingleLinkedList() { clear(); }

  // Copy constructor
  SingleLinkedList(const SingleLinkedList& other)
      : head_(nullptr), tail_(nullptr), size_(0) {
    for (const auto& val : other) {
      push_back(val);
    }
  }

  // Copy assignment
  SingleLinkedList& operator=(const SingleLinkedList& other) {
    if (this != &other) {
      clear();
      for (const auto& val : other) {
        push_back(val);
      }
    }
    return *this;
  }

  // Move constructor
  SingleLinkedList(SingleLinkedList&& other) noexcept
      : head_(other.head_), tail_(other.tail_), size_(other.size_) {
    other.head_ = nullptr;
    other.tail_ = nullptr;
    other.size_ = 0;
  }

  // Move assignment
  SingleLinkedList& operator=(SingleLinkedList&& other) noexcept {
    if (this != &other) {
      clear();
      head_ = other.head_;
      tail_ = other.tail_;
      size_ = other.size_;

      other.head_ = nullptr;
      other.tail_ = nullptr;
      other.size_ = 0;
    }
    return *this;
  }

  bool empty() const { return size_ == 0; }

  void push_front(const ValueType& val) {
    Node* new_node = new Node(val);
    if (head_ == nullptr) {
      head_ = tail_ = new_node;
    } else {
      new_node->next = head_;
      head_ = new_node;
    }
    ++size_;
  }

  void push_back(const ValueType& val) {
    Node* new_node = new Node(val);
    if (tail_ == nullptr) {
      head_ = tail_ = new_node;
    } else {
      tail_->next = new_node;
      tail_ = new_node;
    }
    ++size_;
  }

  void pop_front() {
    assert(!empty());
    Node* tmp = head_;
    head_ = head_->next;
    if (head_ == nullptr) {
      tail_ = nullptr;
    }
    delete tmp;
    --size_;
  }

  ValueType& front() {
    assert(!empty());
    return head_->value;
  }

  const ValueType& front() const {
    assert(!empty());
    return head_->value;
  }

  ValueType& back() {
    assert(!empty());
    return tail_->value;
  }

  const ValueType& back() const {
    assert(!empty());
    return tail_->value;
  }

  size_t size() const { return size_; }

  class Iterator {
  private:
    Node* current_;

  public:
    using iterator_category = std::forward_iterator_tag;
    using value_type = ValueType;
    using difference_type = std::ptrdiff_t;
    using pointer = ValueType*;
    using reference = ValueType&;

    explicit Iterator(Node* node) : current_(node) {}

    reference operator*() const { return current_->value; }
    pointer operator->() const { return &(current_->value); }

    // Prefix increment
    Iterator& operator++() {
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

    bool operator==(const Iterator& other) const {
      return current_ == other.current_;
    }
    bool operator!=(const Iterator& other) const {
      return current_ != other.current_;
    }
  };

  // Returns an iterator to the first element of the list.
  Iterator begin() const { return Iterator(head_); }
  // Returns an iterator to one past the last element of the list.
  Iterator end() const { return Iterator(nullptr); }
};
