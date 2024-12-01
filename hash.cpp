//
// Created by Ben Roberts on 6/12/2023.
//

using namespace std;

#include "hash.h"

Hash::Hash(int n) : tableSize_(n), size_(0) {
  if (n <= 0) {
    throw runtime_error("Error, must be greater than 0 values!");
  }
  elements_ = new LinkedList<int>[n];
}

bool Hash::isEmpty() { return size_ == 0; }

int Hash::getSize() { return size_; }

double Hash::getLoadFactor() { return ((double)size_) / tableSize_; }

int Hash::getTableSize() { return tableSize_; }

void Hash::insert(int data) {
  int index = data % tableSize_;
  if (elements_[index].getSize() == 64) {
    throw runtime_error("Error, hash table is full!");
  } else {
    elements_[index].next(data);
  }
  size_++;
}

int Hash::occurrences(int data) {
  int val = 0;
  LinkedList &curr = elements_[data % tableSize_];
  for (int i = 0; i < curr.getSize() - 2; i++) {
    if (curr.getCurrent() == data) {
      val++;
    }
    curr.next();
  }
  if (curr.getLast() == data) {
    val++;
  }
  return val;
}