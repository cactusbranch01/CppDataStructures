//
// Created by Ben Roberts on 12/21/2022.
//

#include <iostream>
#include "queue.h"
#include "stack.h"
#include "linkedList.h"
#include "hash.h"
using namespace std;

int main()
{
    // Initializes new queue for testing.
    Queue q(64);

    // Adds test items.
    q.add(1);
    q.add(2);
    q.add(3);

    // Tests peek method.
    cout << "The first element is: " << q.peek() << endl;
    q.remove();

    // Tests remove method.
    cout << "The second element is: " << q.remove() << endl;
    q.add(4);
    cout << "The queue size is: " << q.getSize() << endl;
    cout << "The third element is: " << q.remove() << endl;
    cout << "The fourth element is: " << q.remove() << endl;

    // Tests contains method.
    std::cout << std::boolalpha;
    cout << "The element does contain 4: " << bool (q.contains(4) == 0) << endl;

    // Tests removeAll method.
    q.removeAll();
    cout << "After removal the size is: " << q.getSize() << endl;

    // Tests getCap method.
    cout << "The queue max is: " << q.getCap() << endl;

    cout << "\n" << endl;

    // Initializes new stack for testing.
    Stack s(64);

    // Adds test items.
    s.push(1);
    s.push(2);
    s.push(3);

    // Tests peek method.
    cout << "The top element is: " << s.peek() << endl;
    s.pop();

    // Tests remove method.
    cout << "The second element is: " << s.pop() << endl;
    cout << "The stack size is: " << q.getSize() << endl;
    cout << "The last element is: " << s.pop() << endl;

    // Tests contains method.
    std::cout << std::boolalpha;
    cout << "The stack doesn't contain 4: " << bool (q.contains(4) == 0) << endl;

    // Tests removeAll method.
    s.removeAll();
    cout << "After removal the size is: " << s.getSize() << endl;

    // Tests getCap method.
    cout << "The stack max is: " << s.getCap() << endl;

    cout << "\n" << endl;

    // Creates new LinkedList object for testing
    LinkedList l(64, 1);

    // Adds nodes to linked list
    l.add(2);
    l.add(3);

    // Tests next and getCurrent methods.
    cout << "The first node is: " << l.getCurrent() << endl;
    l.next();
    cout << "The second node is: " << l.getCurrent() << endl;
    l.next();
    cout << "The last node is: " << l.getCurrent() << endl;

    // Tests getHead and getLast methods.
    cout << "The head node is: " << l.getHead() << endl;
    cout << "The second node is: " << l.getLast() << endl;

    // Tests size and capacity get methods.
    cout << "The size is: " << l.getSize() << endl;
    cout << "The capacity is: " << l.getCapacity() << endl;

    cout << "\n" << endl;

    // Create a new hash table with 5 buckets
    Hash hashTable(5);

    // Insert some data into the hash table
    hashTable.insert(10);
    hashTable.insert(20);
    hashTable.insert(30);
    hashTable.insert(40);
    hashTable.insert(50);
    hashTable.insert(10);

    // Check if the hash table is empty
    bool isEmpty = hashTable.isEmpty();
    std::cout << "Is hash table empty? " << (isEmpty ? "Yes" : "No") << std::endl;

    // Get the size and load factor of the hash table
    int size = hashTable.getSize();
    double loadFactor = hashTable.getLoadFactor();
    std::cout << "Size of hash table: " << size << std::endl;
    std::cout << "Load factor of hash table: " << loadFactor << std::endl;

    // Get the table size
    int tableSize = hashTable.getTableSize();
    std::cout << "Table size: " << tableSize << std::endl;

    // Count the occurrences of a value in the hash table
    int value = 10;
    int occurrences = hashTable.occurrences(value);
    std::cout << "Occurrences of " << value << " in the hash table: " << occurrences << std::endl;
}