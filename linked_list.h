//
// Created by Ben Roberts on 12/23/2022.
//

#pragma once

#include "node.h"
#include <stdexcept>

using namespace std;

class LinkedList {
  // Fields
  Node *elements;
  int headLoc;
  int currentLoc;
  int lastLoc;
  int size;
  int capacity;

public:
  LinkedList(int cap, int headData);
  LinkedList();
  bool isFull();
  bool isEmpty();
  int getSize();
  int getCapacity();
  void next();
  void add(int data);
  int getHead();
  int getCurrent();
  int getLast();
};