//
// Created by Ben Roberts on 12/21/2022.
//

#include "queue.h"

// Constructor to initialize a new queue object.
// @Param:
//      cap: an int representing the new capacity of the queue.
Queue::Queue(int cap)
{
    elements = new int[cap];
    max = cap;
    first = 0;
    last = -1;
    count = 0;
}

// Method to return the size of the queue.
// @Returns:
//      an int representing the size of the queue.
int Queue::getSize()
{
    return count;
}

// Method to return the capacity of the queue.
// @Returns:
//      an int representing the capacity of the queue.
int Queue::getCap()
{
    return max;
}

// Method to add a new element to the end of the queue.
// @Param:
//      element: an int representing the item to be added.
void Queue::add(int element)
{
    if (isFull())
    {
        throw std::invalid_argument("Error, queue is full!");
    }
    last = (last + 1) % max;
    elements[last] = element;
    count += 1;
}

// Method to remove and return the first element in the queue.
// @Returns:
//      an int representing the removed item.
int Queue::remove()
{
    if (isEmpty())
    {
        throw std::invalid_argument("Error, queue is empty!");
    }
    int temp = elements[first];
    first = (first + 1) % max;
    count -= 1;
    return temp;
}

// Method that returns the first element in the queue.
// @Returns:
//      an int representing the first element in the queue.
int Queue::peek()
{
    if (isEmpty())
    {
        throw std::invalid_argument("Error, queue is empty!");
    }
    return elements[first];
}

// Method that checks if the queue is empty or not.
// @Returns:
//      returns true if the queue is empty and false if it's not.
bool Queue::isEmpty()
{
    return getSize() == 0;
}

// Method that checks if the queue is full or not.
// @Returns:
//      returns true if the queue is full and false if it's not.
bool Queue::isFull()
{
    return getSize() == max;
}

// Method that checks if the queue contains a given element.
// @Returns:
//      true if it contains the element and false if it doesn't.
bool Queue::contains(int element)
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

// Method that removes all the elements in the queue.
void Queue::removeAll()
{
    for (int i = first; i <= last; i++)
    {
        elements[i] = 0;
    }
    count = 0;
}
