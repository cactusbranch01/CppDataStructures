//
// Created by Ben Roberts on 12/23/2022.
//

#include "linked_list.h"

// Constructor to initialize a new Linked List object.
// @Param:
//      cap: an int representing the new capacity of the linked list
//      headData: the data stored in the head node of the linked list
LinkedList::LinkedList(int cap, int headData) {
  if (cap <= 0) {
    throw std::invalid_argument("Error, capacity must be at least 1!");
  }

  // Fields
  elements = new Node[cap];
  elements[0].addData(headData);
  headLoc = 0;
  currentLoc = 0;
  lastLoc = 0;
  size = 1;
  capacity = cap;
}

LinkedList::LinkedList() {
  // Fields
  elements = new Node[64];
  elements[0].addData(0);
  headLoc = 0;
  currentLoc = 0;
  lastLoc = 0;
  size = 1;
  capacity = 64;
}

// Method to check if the linked list is full.
// @Returns:
//      a bool representing if the storage is full.
bool LinkedList::isFull() {
  if (size == capacity) {
    return true;
  }
  return false;
}

// Method to check if the linked list is empty.
// @Returns:
//      a bool representing if the linked list is empty.
bool LinkedList::isEmpty() {
  if (size == 0) {
    return true;
  }
  return false;
}

// Method to get the number of nodes in the linked list.
// @Returns:
//      an int representing the size of the linked list.
int LinkedList::getSize() { return size; }

// Method to get the capacity of the linked list.
// @Returns:
//      an int representing the max size of the linked list.
int LinkedList::getCapacity() { return capacity; }

// Method to iterate to the next node in the linked list.
void LinkedList::next() {
  if (elements[currentLoc].getReference() == 0) {
    throw std::invalid_argument("Error, current node is last node!");
  }

  currentLoc = elements[currentLoc].getReference();
}

// Method to add a new node to the linked list
// @Param:
//      data: an int representing the information to be stored in the new node.
void LinkedList::add(int data) {

  if (isFull()) {
    throw std::invalid_argument("Error, queue is full!");
  }

  // Searches the storage array for an empty cell.
  for (int i = 0; i < capacity - 1; i++) {
    if (elements[i].isEmpty()) {
      int newMemoryLoc = i;
      // Sets the last node to reference the added node's mem location.
      elements[lastLoc].addReference(newMemoryLoc);
      // Sets the new added node.
      elements[newMemoryLoc].addData(data);
      lastLoc = newMemoryLoc;
      size++;
      return;
    }
  }
}

// Method to get the head node in the linked list.
// @Returns:
//      an int representing the data in the head node.
int LinkedList::getHead() { return elements[headLoc].getData(); }

// Method to get the current node in the linked list traversal.
// @Returns:
//      an int representing the data in the current node.
int LinkedList::getCurrent() { return elements[currentLoc].getData(); }

// Method to get the last node in the linked list traversal.
// @Returns:
//      an int representing the data in the last node.
int LinkedList::getLast() { return elements[lastLoc].getData(); }
