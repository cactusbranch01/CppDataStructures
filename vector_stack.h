// Copyright Ben Roberts 2024

#pragma once

#include "vector.h"  // For Vector
#include <stdexcept> // For std::exception

template <typename ValueType> class Stack {
private:
  Vector<ValueType> elements_;

public:
  Stack() : elements_(0) {}

  size_t getSize() const { return elements_.size(); }

  void clear() {
    elements_.clear();
  }

  void push(ValueType element) {
    elements_.push_back(element);
  }

  ValueType peek() {
    if (elements_.empty()) {
      throw std::runtime_error("Cannot peek an empty list!");
    }
    return elements_.back();
  }

  ValueType pop() {
    if (elements_.empty()) {
      throw std::runtime_error("Cannot pop an empty list!");
    }
    ValueType last_element = elements_.back();
    elements_.pop_back();
    return last_element;
  }
};