// Copyright Ben Roberts 2025

#pragma once

#include "linked_list.h"  // For linked lists
#include <cassert>        // For assert

template <typename ValueType> class LinkedDequeue {
private:
  LinkedList<ValueType> *linked_list_;

public:
  LinkedDequeue() { linked_list_ = new LinkedList<ValueType>(); }

  ~LinkedDequeue() {
    linked_list_.clear();
    linked_list_ = nullptr;
  }

  bool isEmpty() { return linked_list_.isEmpty(); }

  size_t size() { return linked_list_.size(); }

  ValueType popLeft() {
    assert(!isEmpty());
    return linked_list_.popFront();
  }

  ValueType popRight() {
    assert(!isEmpty());
    return linked_list_.popBack();
  }

  void pushLeft(const ValueType &val) { linked_list_.pushFront(val); }

  void pushRight(const ValueType &val) { linked_list_.pushLeft(val); }
};