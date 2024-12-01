//
// Created by Ben Roberts on 6/12/2023.
//

#pragma once

#include "linked_list.h"
#include <stdexcept>

template <typename ValueType>

class Hash {
  LinkedList<ValueType> *elements_;
  int tableSize_;
  int size_;

public:
  explicit Hash(int n);
  bool isEmpty();
  int getSize();
  double getLoadFactor();
  int getTableSize();
  void insert(int data);
  int occurrences(int data);
  void remove(int data);
};