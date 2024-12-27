//
// Created by Ben Roberts on 12/23/2022.
//

#pragma once

#include <cstddef>
#include <stdexcept>

using namespace std;

template <typename ValueType>

class LinkedList {
private:
  struct Node {
    ValueType value;
    Node *next;

    Node(const ValueType &val) : value(val), next(nullptr) {}
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
  explicit LinkedList() : head_(nullptr), tail_(nullptr), size_(0) {}

  ~LinkedList() { clear(); }

  void pushFront(const ValueType &value) {
    Node *new_node = new Node(value);
    new_node->next = head_;
    head_ = new_node;
    if (tail_ == nullptr) {
      tail_ = new_node;
    }
    ++size_;
  }

  void pushBack(const ValueType &value) {
    Node *new_node = new Node(value);
    if (tail_ != nullptr) {
      tail_->next = new_node;
      tail_ = new_node;
    } else {
      head_ = tail_ = new_node;
    }
    ++size_;
  }

  void popFront() {
    if (isEmpty()) {
      throw runtime_error("Cannot pop empty list!");
    }
    Node *temp = head_;
    head_ = head_->next;
    delete temp;
    --size_;
    if (head_ == nullptr) {
      tail_ = nullptr;
    }
  }

  void popBack() {
    if (isEmpty()) {
      throw runtime_error("Cannot pop empty list!");
    }
    Node *temp = tail_;
    tail_ = tail_->next;
    delete temp;
    --size_;
    if (tail_ == nullptr) {
      head_ = nullptr;
    }
  }

  ValueType &front() const {
    if (isEmpty()) {
      throw out_of_range("List is empty!");
    }
    return head_->value;
  }

  ValueType &back() const {
    if (isEmpty()) {
      throw out_of_range("List is empty!");
    }
    return tail_->value;
  }

  size_t size() const { return size_; }

  bool isEmpty() const { return size_ == 0; }
};
