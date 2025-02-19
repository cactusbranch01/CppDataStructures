// Created by Ben Roberts 2024

#pragma once

#include "../list/vector.h" // For vectors
#include <cassert>          // For assert

template <typename ValueType> class Stack {
private:
  Vector<ValueType> elements_;

public:
  Stack() : elements_() {}

  size_t size() const { return elements_.size(); }

  bool empty() { return size() == 0; }

  void clear() { elements_.clear(); }

  void push(ValueType element) { elements_.push_back(element); }

  ValueType peek() {
    assert(!empty());
    return elements_.back();
  }

  ValueType pop() {
    assert(!empty());
    ValueType last_element = elements_.back();
    elements_.pop_back();
    return last_element;
  }
};