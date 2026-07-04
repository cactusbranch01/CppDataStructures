// Created by Ben Roberts 2025

#pragma once

#include "../list/linked_list.h" // For linked lists
#include <cassert>               // For assert

template <typename ValueType> class LinkedDequeue {
private:
  LinkedList<ValueType> linked_list_;

public:
  LinkedDequeue() = default;

  bool empty() const { return linked_list_.empty(); }

  size_t size() const { return linked_list_.size(); }

  ValueType popLeft() {
    assert(!empty());
    ValueType val = linked_list_.front();
    linked_list_.pop_front();
    return val;
  }

  ValueType popRight() {
    assert(!empty());
    ValueType val = linked_list_.back();
    linked_list_.pop_back();
    return val;
  }

  void pushLeft(const ValueType& val) { linked_list_.push_front(val); }

  void pushRight(const ValueType& val) { linked_list_.push_back(val); }
};
