#pragma once

#include "../list/vector.h"
#include "../stack/vector_stack.h"

template <typename ValueType> class Pool {
private:
  Vector<ValueType*> allocated_;
  Stack<ValueType*> free_;

public:
  Pool() : allocated_(), free_() {}

  ~Pool() {
    for (ValueType* object : allocated_) {
      delete object;
    }
  }

  Pool(const Pool&) = delete;
  Pool& operator=(const Pool&) = delete;

  ValueType* allocate() {
    if (!free_.empty()) {
      return free_.pop();
    }
    ValueType* object = new ValueType();
    allocated_.push_back(object);
    return object;
  }

  void deallocate(ValueType* object) { free_.push(object); }
};
