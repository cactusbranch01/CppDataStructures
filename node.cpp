//
// Created by Ben Roberts on 12/22/2022.
//

#include "node.h"
using namespace std;

// Constructor to initialize a new Node object.
Node::Node()
{
    // Fields
    reference = 0;
    item = 0;
}

// This method checks if the node is empty.
// @Returns:
//      bool representing whether the node is empty or not
bool Node::isEmpty()
{
    if (reference == 0 && item == 0)
    {
        return true;
    }
    return false;
}

// This method gets the data in the node.
// @Returns:
//      an int representing the contents of the node.
int Node::getData()
{
    return item;
}

// This method gets the reference of a node.
// @Returns:
//      an int representing the reference to the next node in memory.
int Node::getReference()
{
    return reference;
}

// This method adds data to a node.
// @Param:
//      newData: an int representing the new data.
void Node::addData(int newData)
{
    item = newData;
}

// This method adds a reference to a node.
// @Param:
//      newReference: an int representing the new reference.
void Node::addReference(int newReference)
{
    reference = newReference;
}