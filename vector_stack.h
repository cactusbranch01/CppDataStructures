// Copyright Ben Roberts 2024

#pragma once

#include "vector.h"  // For Vector
#include <cassert>   // For assert

template <typename ValueType> class Stack {
private:
  Vector<ValueType> elements_;

public:
  Stack() : elements_() {}

  size_t getSize() const { return elements_.size(); }

  bool isEmpty() { return getSize() == 0; }

  void clear() {
    elements_.clear();
  }

  void push(ValueType element) {
    elements_.push_back(element);
  }

  ValueType peek() {
    assert(!isEmpty());
    return elements_.back();
  }

  ValueType pop() {
    assert(!isEmpty());
    ValueType last_element = elements_.back();
    elements_.pop_back();
    return last_element;
  }
};