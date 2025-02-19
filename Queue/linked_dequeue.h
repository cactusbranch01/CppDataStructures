// Created by Ben Roberts 2025

#pragma once

#include "../list/linked_list.h" // For linked lists
#include <cassert>               // For assert

template <typename ValueType> class LinkedDequeue {
private:
  LinkedList<ValueType> *linked_list_;

public:
  LinkedDequeue() { linked_list_ = new LinkedList<ValueType>(); }

  ~LinkedDequeue() {
    linked_list_.clear();
    linked_list_ = nullptr;
  }

  bool empty() { return linked_list_.empty(); }

  size_t size() { return linked_list_.size(); }

  ValueType popLeft() {
    assert(!empty());
    return linked_list_.pop_front();
  }

  ValueType popRight() {
    assert(!empty());
    return linked_list_.pop_back();
  }

  void pushLeft(const ValueType &val) { linked_list_.push_front(val); }

  void pushRight(const ValueType &val) { linked_list_.pushLeft(val); }
};