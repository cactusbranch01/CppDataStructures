//
// Created by Ben Roberts on 12/22/2022.
//

#ifndef DATASTRUCTURESC___NODE_H
#define DATASTRUCTURESC___NODE_H

#include <stdexcept>
using namespace std;

class Node {
    int item;
    int reference;

public:
    explicit Node();
    bool isEmpty();
    int getData();
    int getReference();
    void addData(int newData);
    void addReference(int newReference);
};

#endif
