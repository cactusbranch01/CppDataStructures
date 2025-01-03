// Copyright Ben Roberts 2025

#pragma once

#include "linked_list.h"
#include <stdexcept>

template <typename ValueType> class LinkedDequeue {
private:
  LinkedList<ValueType> *linked_list_;
public:
  LinkedDequeue() {
    linked_list_ = new LinkedList<ValueType>();
  }

  ~LinkedDequeue() {
    linked_list_.clear();
    linked_list_ = nullptr;
  }

  bool isEmpty() { return linked_list_.isEmpty(); }

  size_t size() { return linked_list_.size(); }

  ValueType popLeft() {
    if (isEmpty()) {
      throw std::runtime_error("Cannot popleft from an empty deque!");
    }
    return linked_list_.popFront();
  }

  ValueType popRight() {
    if (isEmpty()) {
      throw std::runtime_error("Cannot pop from an empty dequeue dequeue!");
    }
    return linked_list_.popBack();
  }

  void pushLeft(const ValueType& val) {
    linked_list_.pushFront(val);
  }

  void pushRight(const ValueType& val) {
    linked_list_.pushLeft(val);
  }
};