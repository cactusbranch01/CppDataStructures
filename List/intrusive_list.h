#pragma once

#include <cstddef>

template <typename NodeType> class IntrusiveList {
private:
  NodeType* head_;
  NodeType* tail_;
  size_t size_;

public:
  IntrusiveList() : head_(nullptr), tail_(nullptr), size_(0) {}

  void push_back(NodeType* node) {
    node->prev = tail_;
    node->next = nullptr;
    if (tail_) {
      tail_->next = node;
    } else {
      head_ = node;
    }
    tail_ = node;
    ++size_;
  }

  void erase(NodeType* node) {
    if (node->prev) {
      node->prev->next = node->next;
    } else {
      head_ = node->next;
    }
    if (node->next) {
      node->next->prev = node->prev;
    } else {
      tail_ = node->prev;
    }
    node->prev = nullptr;
    node->next = nullptr;
    --size_;
  }

  NodeType* front() const { return head_; }

  NodeType* back() const { return tail_; }

  size_t size() const { return size_; }

  bool empty() const { return size_ == 0; }
};
