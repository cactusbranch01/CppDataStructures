// Copyright Ben Roberts 2024

#pragma once

#include <stdexcept>
#include <vector>

template <typename ValueType> class Stack {
private:
  std::vector<ValueType> elements_;
  size_t size_;

public:
  Stack() : elements_(0), size_(0) {}

  size_t getSize() { return size_; }

  void clear() {
    size_ = 0;
    elements_.clear();
  }

  void push(ValueType element) {
    elements_.push_back(element);
    size_++;
  }

  ValueType peek() {
    if (getSize() == 0) {
      throw std::runtime_error("Cannot peek an empty list!");
    }
    return elements_[size_ - 1];
  }

  ValueType pop() {
    if (getSize() == 0) {
      throw std::runtime_error("Cannot pop an empty list!");
    }
    ValueType last_element = elements_[size_ - 1];
    elements_.pop_back();
    size_--;
    return last_element;
  }
};