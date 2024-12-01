//
// Created by Ben Roberts on 12/21/2022.
//

#include "queue.h"

using namespace std;

Queue::Queue(int cap) : first_(0), last_(-1), count_(0), max_(cap) {
  elements_ = new int[cap];
}

int Queue::getSize() { return count_; }

int Queue::getCap() { return max_; }

void Queue::add(int element) {
  if (isFull()) {
    throw runtime_error("Error, queue is full!");
  }
  last_ = (last_ + 1) % max_;
  elements_[last_] = element;
  count_ += 1;
}

int Queue::remove() {
  if (isEmpty()) {
    throw runtime_error("Error, queue is empty!");
  }
  int temp = elements_[first_];
  first_ = (first_ + 1) % max_;
  count_ -= 1;
  return temp;
}

int Queue::peek() {
  if (isEmpty()) {
    throw runtime_error("Error, queue is empty!");
  }
  return elements_[first_];
}

bool Queue::isEmpty() { return count_ == 0; }

bool Queue::isFull() { return count_ == max_; }

bool Queue::contains(int element) {
  for (int i = first_; i <= last_; i++) {
    if (elements_[i] == element) {
      return true;
    }
  }
  return false;
}

void Queue::removeAll() {
  for (int i = first_; i <= last_; i++) {
    elements_[i] = 0;
  }
  count_ = 0;
}