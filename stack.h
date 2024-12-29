// Copyright Ben Roberts 2024

#pragma once

#include <stdexcept>
#include <vector>

using namespace std;

template <typename ValueType> class Stack {
private:
  vector<ValueType> elements_;
  size_t size_;
  size_t last_;

public:
  Stack(size_t capacity = 16) : size_(0), last_(0), elements_(capacity) {}

  size_t getSize() { return size_; }

  void clear() {
    size_ = 0;
    last_ = 0;
    elements_.clear();
  }

  void push(ValueType element) { elements_.push_back(element); }

  ValueType peek() { return elements_[last_]; }

  ValueType pop() {
    ValueType last_element = elements_[last_];
    elements_.pop_back();
    return last_element;
  }
};