//
// Created by Ben Roberts on 6/12/2023.
//

// We need to introduce a C++ hash function

#include "hash.h"

// Constructor to initialize a new hash object.
// @Param:
//      n: an int representing the number of buckets of the hash table
Hash::Hash(int n)
{
    if (n <= 0)
    {
        throw std::invalid_argument("Error, must be greater than 0 values!");
    }

    // Fields
    elements = new LinkedList[n];
    tableSize = n;
    size = 0;
}

// Method to check if the hash table is empty.
// @Returns:
//      a bool representing the whether the hash table is empty.
bool Hash::isEmpty()
{
    if (size == 0)
    {
        return true;
    }
    return false;
}

// Method to get the number of non-empty nodes in the hash table.
// @Returns:
//      an int representing the size of the hash table.
int Hash::getSize()
{
    return size;
}

// Method to get the load factor of the hash table.
// @Returns:
//      a double representing the ratio of the size to the table size.
double Hash::getLoadFactor()
{
    return ((double) size) / tableSize;
}

// Method to get the size of the hash table.
// @Returns:
//      an int representing the size of the hash table.
int Hash::getTableSize()
{
    return tableSize;
}

// Method to insert new data into the hash table.
// @Param:
//      data: an int representing the information to be stored in the new node.
void Hash::insert(int data)
{
    int index = data % tableSize;
    if (elements[index].getSize() == 64)
    {
        throw std::invalid_argument("Error, hash table is full!");
    }
    else
    {
        elements[index].add(data);
    }
    size++;
}

// Method to find the number of times an int reappears in the table.
// @Param:
//      data: an int representing data to be searched for.
// @Returns:
//      an int representing the number of occurrences
int Hash::occurrences(int data)
{
    int val = 0;
    LinkedList& curr = elements[data % tableSize];
    for (int i = 0; i < curr.getSize() - 2; i++)
    {
        if (curr.getCurrent() == data)
        {
            val++;
        }
        curr.next();
    }
    if (curr.getLast() == data)
    {
        val++;
    }
    return val;
}

