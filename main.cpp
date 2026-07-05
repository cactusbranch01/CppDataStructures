//
// Created by Ben Roberts on 2024.
//

#include "hashing/chaining_linked_hash.h" // For chaining list hashtables
#include "hashing/chaining_vector_hash.h" // For chaining vector hashtables
#include "hashing/open_address_hash.h"    // For open address hashtables
#include "list/linked_list.h"             // For linked lists
#include "list/vector.h"                  // For vectors
#include "queue/circular_vector_queue.h"  // For circular vector queues
#include "queue/linked_dequeue.h"         // For linked dequeues
#include "stack/linked_stack.h"           // For linked list stacks
#include "stack/vector_stack.h"           // For vector stacks
#include "tree/bst.h"                     // For binary search trees
#include "tree/red_black_tree.h"          // For red-black trees
#include <algorithm>                      // For std::shuffle
#include <cassert>                        // For asserts
#include <chrono>                         // For timers
#include <iostream>                       // For stdout
#include <random>                         // For std::mt19937
#include <string>                         // For std::string
#include <vector>                         // For shuffled test keys

void testVector(size_t testSize) {
  Vector<int> vec;

  // Insertion
  auto insertStart = std::chrono::high_resolution_clock::now();
  for (int i = 0; i < static_cast<int>(testSize); ++i) {
    vec.push_back(i);
  }
  auto insertEnd = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> insertDuration = insertEnd - insertStart;
  std::cout << "Insertion of " << testSize << " elements in the vector took "
            << insertDuration.count() << " seconds.\n";
  assert(vec.size() == testSize &&
         "Vector size should match the number of inserted elements");

  // Retrieval using Iterator
  auto retrieveStart = std::chrono::high_resolution_clock::now();
  size_t index = 0;
  for (const auto& value : vec) {
    assert(value == static_cast<int>(index) &&
           "Retrieved value should match the inserted value");
    ++index;
  }
  auto retrieveEnd = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> retrieveDuration = retrieveEnd - retrieveStart;
  std::cout << "Retrieval of " << testSize
            << " elements in the vector using iterator took "
            << retrieveDuration.count() << " seconds.\n";

  // Additional Tests: front() and back()
  if (testSize > 0) {
    assert(vec.front() == 0 &&
           "Front element should be the first inserted value");
    assert(vec.back() == static_cast<int>(testSize - 1) &&
           "Back element should be the last inserted value");
  }
  std::cout << "All vector tests passed successfully.\n" << std::endl;}

void testVectorStack(size_t testSize) {
  Stack<std::pair<int, std::string>> stack;

  // Insertion
  auto insertStart = std::chrono::high_resolution_clock::now();
  for (int i = 0; i < static_cast<int>(testSize); ++i) {
    stack.push({i, "Value_" + std::to_string(i)});
  }
  auto insertEnd = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> insertDuration = insertEnd - insertStart;
  std::cout << "Insertion of " << testSize
            << " elements in the vector stack took " << insertDuration.count()
            << " seconds.\n";
  assert(stack.size() == testSize &&
         "Stack size should match the number of inserted elements");

  // Peek at the top element
  auto top = stack.peek();
  assert(top.first == static_cast<int>(testSize - 1) &&
         "Top element key should be the last inserted key");
  assert(top.second == "Value_" + std::to_string(testSize - 1) &&
         "Top element value should be the last inserted value");

  // Removal
  auto removeStart = std::chrono::high_resolution_clock::now();
  for (int i = static_cast<int>(testSize) - 1; i >= 0; --i) {
    auto element = stack.pop();
    assert(element.first == i &&
           "Popped element key should match the expected key");
    assert(element.second == "Value_" + std::to_string(i) &&
           "Popped element value should match the expected value");
  }
  auto removeEnd = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> removeDuration = removeEnd - removeStart;
  std::cout << "Removal of " << testSize
            << " elements from the vector stack took " << removeDuration.count()
            << " seconds.\n";
  assert(stack.size() == 0 &&
         "Stack should be empty after popping all elements");
  std::cout << "All vector stack tests passed successfully.\n" << std::endl;}

void testLinkedStack(size_t testSize) {
  LinkedStack<std::pair<int, std::string>> stack;

  // Insertion
  auto insertStart = std::chrono::high_resolution_clock::now();
  for (int i = 0; i < static_cast<int>(testSize); ++i) {
    stack.push({i, "Value_" + std::to_string(i)});
  }
  auto insertEnd = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> insertDuration = insertEnd - insertStart;
  std::cout << "Insertion of " << testSize
            << " elements in the linked list stack took " << insertDuration.count()
            << " seconds.\n";
  assert(stack.size() == testSize &&
         "Stack size should match the number of inserted elements");

  // Peek at the top element
  auto top = stack.peek();
  assert(top.first == static_cast<int>(testSize - 1) &&
         "Top element key should be the last inserted key");
  assert(top.second == "Value_" + std::to_string(testSize - 1) &&
         "Top element value should be the last inserted value");

  // Removal
  auto removeStart = std::chrono::high_resolution_clock::now();
  for (int i = static_cast<int>(testSize) - 1; i >= 0; --i) {
    auto element = stack.pop();
    assert(element.first == i &&
           "Popped element key should match the expected key");
    assert(element.second == "Value_" + std::to_string(i) &&
           "Popped element value should match the expected value");
  }
  auto removeEnd = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> removeDuration = removeEnd - removeStart;
  std::cout << "Removal of " << testSize
            << " elements from the linked list stack took " << removeDuration.count()
            << " seconds.\n";
  assert(stack.size() == 0 &&
         "Stack should be empty after popping all elements");
  std::cout << "All linked stack tests passed successfully.\n" << std::endl;}

void testCircularVectorQueue(size_t testSize) {
  CircularVectorQueue<std::pair<int, std::string>> queue;

  // Insertion
  auto insertStart = std::chrono::high_resolution_clock::now();
  for (int i = 0; i < static_cast<int>(testSize); ++i) {
    queue.push({i, "Value_" + std::to_string(i)});
  }
  auto insertEnd = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> insertDuration = insertEnd - insertStart;
  std::cout << "Insertion of " << testSize
            << " elements in the vector queue took " << insertDuration.count()
            << " seconds.\n";
  assert(queue.size() == testSize &&
         "Queue size should match the number of inserted elements");

  // Peek
  auto front = queue.peek();
  assert(front.first == 0 &&
         "Front element key should be the first inserted key");
  assert(front.second == "Value_0" &&
         "Front element value should be the first inserted value");

  // Removal
  auto removeStart = std::chrono::high_resolution_clock::now();
  for (int i = 0; i < static_cast<int>(testSize); ++i) {
    auto element = queue.pop_front();
    assert(element.first == i &&
           "Popped element key should match the expected key");
    assert(element.second == "Value_" + std::to_string(i) &&
           "Popped element value should match the expected value");
  }
  auto removeEnd = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> removeDuration = removeEnd - removeStart;
  std::cout << "Removal of " << testSize
            << " elements from the vector queue took " << removeDuration.count()
            << " seconds.\n";
  assert(queue.size() == 0 &&
         "Queue should be empty after popping all elements");
  std::cout << "All vector queue tests passed successfully.\n" << std::endl;}

void testLinkedList(size_t testSize) {
  LinkedList<std::pair<int, std::string>> linkedList;

  // Insertion
  auto insertStart = std::chrono::high_resolution_clock::now();
  for (int i = 0; i < (int)testSize; ++i) {
    linkedList.push_back({i, "Value_" + std::to_string(i)});
  }
  auto insertEnd = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> insertDuration = insertEnd - insertStart;
  std::cout << "Insertion of " << testSize
            << " elements in the linked list took " << insertDuration.count()
            << " seconds.\n";

  assert(linkedList.size() == testSize &&
         "Linked list size should match the number of inserted elements");

  // Itertator
  auto retrieveStart = std::chrono::high_resolution_clock::now();
  size_t index = 0;
  for (const auto& pair : linkedList) {
    assert(pair.first == static_cast<int>(index) &&
           "Retrieved key should match the inserted key");
    std::string expectedValue = "Value_" + std::to_string(index);
    assert(pair.second == expectedValue &&
           "Retrieved value should match the inserted value");
    ++index;
  }
  auto retrieveEnd = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> retrieveDuration = retrieveEnd - retrieveStart;
  std::cout << "Retrieval of " << testSize
            << " elements in the linked list took " << retrieveDuration.count()
            << " seconds.\n";

  // Removal
  auto removeStart = std::chrono::high_resolution_clock::now();
  for (size_t i = 0; i < testSize; ++i) {
    linkedList.pop_front();
  }
  auto removeEnd = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> removeDuration = removeEnd - removeStart;
  std::cout << "Removal of " << testSize
            << " elements from the linked list took " << removeDuration.count()
            << " seconds.\n";

  assert(linkedList.empty() &&
         "Linked list should be empty after popping all elements");
  std::cout << "All tests passed successfully.\n" << std::endl;}

void testOpenAddressing(size_t testSize) {
  OpenAddressHash<int, std::string> openHash;

  // Insertion
  auto start = std::chrono::high_resolution_clock::now();
  for (size_t i = 0; i < testSize; ++i) {
    openHash.insert(i, "Value_" + std::to_string(i));
  }
  auto insertEnd = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> insertDuration = insertEnd - start;
  std::cout << "Insertion of " << testSize
            << " elements in an open address hashtable took "
            << insertDuration.count() << " seconds.\n";
  assert(openHash.size() == testSize &&
         "Hash table size should match the number of inserted elements");

  // Retrieval
  auto retrieveStart = std::chrono::high_resolution_clock::now();
  for (size_t i = 0; i < testSize; ++i) {
    std::string expectedValue = "Value_" + std::to_string(i);
    assert(openHash.get(i) == expectedValue &&
           "Retrieved value should match the inserted value");
  }
  auto retrieveEnd = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> retrieveDuration = retrieveEnd - retrieveStart;
  std::cout << "Retrieval of " << testSize
            << " elements in an open address hashtable took "
            << retrieveDuration.count() << " seconds.\n";
  std::cout << "All open adddress hash tests passed successfully.\n" << std::endl;}

void testChainingVectorHash(size_t testSize) {
  ChainingVectorHash<int, std::string> chainingHash;

  // Insertion
  auto start = std::chrono::high_resolution_clock::now();
  for (size_t i = 0; i < testSize; ++i) {
    chainingHash.insert(i, "Value_" + std::to_string(i));
  }
  auto insertEnd = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> insertDuration = insertEnd - start;
  std::cout << "Insertion of " << testSize
            << " elements in a vector chaining hashtable took "
            << insertDuration.count() << " seconds.\n";
  assert(chainingHash.size() == testSize &&
         "Hash table size should match the number of inserted elements");

  // Retrieval
  auto retrieveStart = std::chrono::high_resolution_clock::now();
  for (size_t i = 0; i < testSize; ++i) {
    std::string expectedValue = "Value_" + std::to_string(i);
    assert(chainingHash.get(i) == expectedValue &&
           "Retrieved value should match the inserted value");
  }
  auto retrieveEnd = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> retrieveDuration = retrieveEnd - retrieveStart;
  std::cout << "Retrieval of " << testSize
            << " elements in a vector chaining hashtable took "
            << retrieveDuration.count() << " seconds.\n";
  std::cout << "All vector chaining hash tests passed successfully.\n" << std::endl;
}

void testChainingLinkedHash(size_t testSize) {
  ChainingLinkedHash<int, std::string> chainingHash;

  // Insertion
  auto start = std::chrono::high_resolution_clock::now();
  for (size_t i = 0; i < testSize; ++i) {
    chainingHash.insert(i, "Value_" + std::to_string(i));
  }
  auto insertEnd = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> insertDuration = insertEnd - start;
  std::cout << "Insertion of " << testSize
            << " elements in a linked list chaining hashtable took "
            << insertDuration.count() << " seconds.\n";
  assert(chainingHash.size() == testSize &&
         "Hash table size should match the number of inserted elements");

  // Retrieval
  auto retrieveStart = std::chrono::high_resolution_clock::now();
  for (size_t i = 0; i < testSize; ++i) {
    std::string expectedValue = "Value_" + std::to_string(i);
    assert(chainingHash.get(i) == expectedValue &&
           "Retrieved value should match the inserted value");
  }
  auto retrieveEnd = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> retrieveDuration = retrieveEnd - retrieveStart;
  std::cout << "Retrieval of " << testSize
            << " elements in a linked list chaining hashtable took "
            << retrieveDuration.count() << " seconds.\n";
  std::cout << "All linked chaining hashing tests passed successfully.\n" << std::endl;}

void testBST(size_t testSize) {
  BST<int> bst;

  // Insert keys in shuffled order so the unbalanced tree stays close to
  // O(log n) height instead of degenerating into a linked list
  std::vector<int> keys(testSize);
  for (size_t i = 0; i < testSize; ++i) {
    keys[i] = static_cast<int>(i);
  }
  std::mt19937 rng(42);
  std::shuffle(keys.begin(), keys.end(), rng);

  // Insertion
  auto insertStart = std::chrono::high_resolution_clock::now();
  for (int key : keys) {
    bst.insert(key);
  }
  auto insertEnd = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> insertDuration = insertEnd - insertStart;
  std::cout << "Insertion of " << testSize << " elements in the BST took "
            << insertDuration.count() << " seconds.\n";
  assert(bst.size() == testSize &&
         "BST size should match the number of inserted elements");

  // Duplicate insertion should not change the size
  bst.insert(0);
  assert(bst.size() == testSize &&
         "Inserting a duplicate value should not change the BST size");

  // Retrieval
  auto retrieveStart = std::chrono::high_resolution_clock::now();
  for (int i = 0; i < static_cast<int>(testSize); ++i) {
    assert(bst.contains(i) && "BST should contain every inserted value");
  }
  auto retrieveEnd = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> retrieveDuration = retrieveEnd - retrieveStart;
  std::cout << "Retrieval of " << testSize << " elements in the BST took "
            << retrieveDuration.count() << " seconds.\n";
  assert(!bst.contains(static_cast<int>(testSize)) &&
         "BST should not contain a value that was never inserted");

  // Min and max
  assert(bst.min() == 0 && "Min should be the smallest inserted value");
  assert(bst.max() == static_cast<int>(testSize - 1) &&
         "Max should be the largest inserted value");

  // Rule of 3: copies should be deep and independent of the original
  BST<int> copy(bst);
  assert(copy.size() == bst.size() &&
         "Copied BST size should match the original");
  copy.remove(0);
  assert(!copy.contains(0) &&
         "Removed value should be gone from the copied BST");
  assert(bst.contains(0) &&
         "Removing from the copy should not affect the original");

  // Removal
  auto removeStart = std::chrono::high_resolution_clock::now();
  for (int key : keys) {
    bst.remove(key);
  }
  auto removeEnd = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> removeDuration = removeEnd - removeStart;
  std::cout << "Removal of " << testSize << " elements from the BST took "
            << removeDuration.count() << " seconds.\n";
  assert(bst.size() == 0 &&
         "BST should be empty after removing all elements");
  assert(bst.empty() && "BST should report empty after removing all elements");
  std::cout << "All BST tests passed successfully.\n" << std::endl;}

void testRedBlackTree(size_t testSize) {
  RedBlackTree<int> tree;

  // Insertion (sequential keys are fine because the tree self-balances)
  auto insertStart = std::chrono::high_resolution_clock::now();
  for (int i = 0; i < static_cast<int>(testSize); ++i) {
    tree.insert(i);
  }
  auto insertEnd = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> insertDuration = insertEnd - insertStart;
  std::cout << "Insertion of " << testSize
            << " elements in the red-black tree took "
            << insertDuration.count() << " seconds.\n";
  assert(tree.size() == testSize &&
         "Red-black tree size should match the number of inserted elements");
  assert(tree.isValid() &&
         "Red-black tree should satisfy all red-black properties after "
         "insertion");

  // Duplicate insertion should not change the size
  tree.insert(0);
  assert(tree.size() == testSize &&
         "Inserting a duplicate value should not change the tree size");

  // Retrieval
  auto retrieveStart = std::chrono::high_resolution_clock::now();
  for (int i = 0; i < static_cast<int>(testSize); ++i) {
    assert(tree.contains(i) &&
           "Red-black tree should contain every inserted value");
  }
  auto retrieveEnd = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> retrieveDuration = retrieveEnd - retrieveStart;
  std::cout << "Retrieval of " << testSize
            << " elements in the red-black tree took "
            << retrieveDuration.count() << " seconds.\n";
  assert(!tree.contains(static_cast<int>(testSize)) &&
         "Red-black tree should not contain a value that was never inserted");

  // Min and max
  assert(tree.min() == 0 && "Min should be the smallest inserted value");
  assert(tree.max() == static_cast<int>(testSize - 1) &&
         "Max should be the largest inserted value");

  // Rule of 3: copies should be deep and independent of the original
  RedBlackTree<int> copy(tree);
  assert(copy.size() == tree.size() &&
         "Copied tree size should match the original");
  assert(copy.isValid() &&
         "Copied tree should satisfy all red-black properties");
  copy.remove(0);
  assert(!copy.contains(0) &&
         "Removed value should be gone from the copied tree");
  assert(tree.contains(0) &&
         "Removing from the copy should not affect the original");

  // Removal
  auto removeStart = std::chrono::high_resolution_clock::now();
  for (int i = 0; i < static_cast<int>(testSize); ++i) {
    tree.remove(i);
  }
  auto removeEnd = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> removeDuration = removeEnd - removeStart;
  std::cout << "Removal of " << testSize
            << " elements from the red-black tree took "
            << removeDuration.count() << " seconds.\n";
  assert(tree.size() == 0 &&
         "Red-black tree should be empty after removing all elements");
  assert(tree.empty() &&
         "Red-black tree should report empty after removing all elements");
  assert(tree.isValid() && "An empty red-black tree should be valid");
  std::cout << "All red-black tree tests passed successfully.\n" << std::endl;}

int main() {
  testVector(1'000'000);
  testLinkedList(1'000'000);

  testLinkedStack(1'000'000);
  testVectorStack(1'000'000);

  testCircularVectorQueue(1'000'000);
  testOpenAddressing(1'000'000);
  testChainingVectorHash(1'000'000);
  testChainingLinkedHash(1'000'000);

  testBST(1'000'000);
  testRedBlackTree(1'000'000);
  return 0;
}