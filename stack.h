//
// Created by Ben Roberts on 12/22/2022.
//

#pragma once

#include <stdexcept>
using namespace std;

class Stack {
  int *elements_;
  int first_;
  int last_;
  int count_;
  int max_;

public:
  explicit Stack(int cap);
  int getSize();
  int getCap();
  void push(int element);
  int pop();
  int peek();
  bool isEmpty();
  bool isFull();
  bool contains(int element);
  void removeAll();
};