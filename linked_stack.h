// Copyright Ben Roberts 2025

#include "linked_list.h"  // For linked_list.h

template <typename ValueType>
class LinkedStack {
private:
  LinkedList<ValueType> linked_list_;
public:
  LinkedStack() : linked_list_() {};

  void clear() {
    linked_list_.clear();
  }

  size_t size() {
    return linked_list_.size();
  }

  bool empty() {
    return linked_list_.empty();
  }

  ValueType &peek() const {
    assert(!empty());
    return linked_list_.back()
  }

  ValueType &pop() {
    assert(!empty());
    auto back = std::move(linked_list_.back());
    linked_list_.popBack();
    return back;
  }

  void push(const ValueType& val) {
    linked_list_.pushBack(val);
  }
};
