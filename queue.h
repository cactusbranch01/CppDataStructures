//
// Created by benrr on 12/21/2022.
//

#pragma once

#include <stdexcept>

using namespace std;

class Queue {
  int *elements_;
  int first_;
  int last_;
  int count_;
  int max_;

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