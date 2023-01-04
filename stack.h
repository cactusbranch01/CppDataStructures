//
// Created by Ben Roberts on 12/22/2022.
//

#ifndef DATASTRUCTURESC___STACK_H
#define DATASTRUCTURESC___STACK_H

#include <stdexcept>
using namespace std;

// This Stack class implements the stack data structure.
class Stack
{
    // Fields
    int *elements;
    int first;
    int last;
    int count;
    int max;

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

#endif
