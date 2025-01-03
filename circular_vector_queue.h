// Copyright Ben Roberts 2024

#pragma once

#include <cassert>    // For asserts
#include <stdexcept>  // For std::exception
#include "vector.h"   // For Vector

template <typename ValueType> class CircularVectorQueue {
private:
  Vector<ValueType> elements_;
  size_t capacity_;
  size_t size_;
  size_t front_;
  size_t back_;

  void resize(size_t new_capacity) {
    assert(capacity_ != 0);
    auto old_elements = elements_;
    elements_ = Vector<ValueType>(new_capacity);
    for (size_t i = 0; i < size_; i++) {
      elements_[i] = old_elements[(i + front_) % capacity_];
    }
    capacity_ = new_capacity;
    front_ = 0;
    back_ = (size_ > 0) ? size_ : 0;
  }

public:
  explicit CircularVectorQueue()
      : elements_(16), capacity_(16), size_(0), front_(0), back_(0) {}

  size_t getSize() { return size_; }

  void push(ValueType element) {
    if (size_ + 1 > capacity_) {
      resize(capacity_ * 2);
    }
    elements_[back_] = element;
    back_ = (back_ + 1) % capacity_;
    size_++;
  }

  ValueType peek() {
    if (getSize() == 0) {
      throw std::runtime_error("Cannot peek an empty queue");
    }
    return elements_[front_];
  }

  ValueType popFront() {
    if (getSize() == 0) {
      throw std::runtime_error("Cannot pop an empty queue");
    }
    size_--;
    ValueType first = elements_[front_];
    front_ = (front_ + 1) % capacity_;
    return first;
  }
};