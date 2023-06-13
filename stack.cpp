//
// Created by Ben Roberts on 12/22/2022.
//

#include "stack.h"

// Constructor to initialize a new stack object.
// @Param:
//      cap: an int representing the new capacity of the stack.
Stack::Stack(int cap)
{
    elements = new int[cap];
    max = cap;
    first = 0;
    last = -1;
    count = 0;
}

// Method to return the size of the stack.
// @Returns:
//      an int representing the size of the stack.
int Stack::getSize()
{
    return count;
}

// Method to return the capacity of the stack.
// @Returns:
//      an int representing the capacity of the stack.
int Stack::getCap()
{
    return max;
}

// Method to add a new element to the top of the stack.
// @Param:
//      element: an int representing the item to be added.
void Stack::push(int element)
{
    if (isFull())
    {
        throw std::invalid_argument("Error, stack is full!");
    }
    last = (last + 1) % max;
    elements[last] = element;
    count += 1;
}

// Method to pop and return the last element in the stack.
// @Returns:
//      an int representing the popped item.
int Stack::pop()
{
    if (isEmpty())
    {
        throw std::invalid_argument("Error, stack is empty!");
    }
    int temp = elements[last];
    last = (last - 1);
    count -= 1;
    return temp;
}

// Method that returns the top element of the stack without removing it.
// @Returns:
//      an int representing the last element in the stack.
int Stack::peek()
{
    if (isEmpty())
    {
        throw std::invalid_argument("Error, stack is empty!");
    }
    return elements[last];
}

// Method that checks if the stack is empty or not.
// @Returns:
//      returns true if the stack is empty and false if it's not.
bool Stack::isEmpty()
{
    return getSize() == 0;
}

// Method that checks if the stack is full or not.
// @Returns:
//      returns true if the stack is full and false if it's not.
bool Stack::isFull()
{
    return getSize() == max;
}

// Method that checks if the stack contains a given element.
// @Returns:
//      true if it contains the element and false if it doesn't.
bool Stack::contains(int element)
{
    for (int i = first; i <= last; i++)
    {
        if (elements[i] == element)
        {
            return true;
        }
    }
    return false;
}

// Method that removes all the elements in the stack.
void Stack::removeAll()
{
    for (int i = first; i <= last; i++)
    {
        elements[i] = 0;
    }
    count = 0;
}



