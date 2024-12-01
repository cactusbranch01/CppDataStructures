//
// Created by Ben Roberts on 6/12/2023.
//

#ifndef DATASTRUCTURESC___HASH_H
#define DATASTRUCTURESC___HASH_H

#include "linked_list.h"
#include "node.h"
#include <stdexcept>


class Hash {
  // Fields
  LinkedList *elements;
  int tableSize;
  int size;

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

#endif // DATASTRUCTURESC___HASH_H
