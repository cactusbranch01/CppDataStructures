//
// Created by Ben Roberts on 12/22/2022.
//

#include "stack.h"

using namespace std;

Stack::Stack(int cap) : first_(0), last_(-1), count_(0), max_(cap) {
  elements_ = new int[cap];
}

int Stack::getSize() { return count_; }

int Stack::getCap() { return max_; }

void Stack::push(int element) {
  if (isFull()) {
    throw runtime_error("Error, stack is full!");
  }
  last_ = (last_ + 1) % max_;
  elements_[last_] = element;
  count_ += 1;
}

int Stack::pop() {
  if (isEmpty()) {
    throw std::invalid_argument("Error, stack is empty!");
  }
  int temp = elements_[last_];
  last_ -= 1;
  count_ -= 1;
  return temp;
}

int Stack::peek() {
  if (isEmpty()) {
    throw std::invalid_argument("Error, stack is empty!");
  }
  return elements_[last_];
}

bool Stack::isEmpty() { return count_ == 0; }

bool Stack::isFull() { return count_ == max_; }

bool Stack::contains(int element) {
  for (int i = first_; i <= last_; i++) {
    if (elements_[i] == element) {
      return true;
    }
  }
  return false;
}

void Stack::removeAll() {
  for (int i = first_; i <= last_; i++) {
    elements_[i] = 0;
  }
  count_ = 0;
}
