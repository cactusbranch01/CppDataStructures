//
// Created by benrr on 12/21/2022.
//

#ifndef DATASTRUCTURESC___QUEUE_H
#define DATASTRUCTURESC___QUEUE_H

#include <stdexcept>
using namespace std;

// This Queue class implements the queue data structure.
class Queue {
  // Fields
  int *elements;
  int first;
  int last;
  int count;
  int max;

public:
  explicit Queue(int cap);
  int getSize();
  int getCap();
  void add(int element);
  int remove();
  int peek();
  bool isEmpty();
  bool isFull();
  bool contains(int element);
  void removeAll();
};

#endif
