//
// Created by Ben Roberts on 12/21/2022.
//

#include "chaining.cpp"
#include "linked_list.cpp"
#include "open_address.cpp"
#include "queue.h"
#include "stack.h"
#include <cassert>
#include <chrono>
#include <iostream>
#include <string>

using namespace std;

int testOpenAddressing(size_t testSize) {
  OpenAddressTable<int, std::string> openHash;
  auto start = std::chrono::high_resolution_clock::now();
  for (size_t i = 0; i < testSize; ++i) {
    openHash.insert(i, "Value_" + std::to_string(i));
  }
  auto insertEnd = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> insertDuration = insertEnd - start;
  std::cout << "Insertion of " << testSize
            << " elements in an open address hashtable took "
            << insertDuration.count() << " seconds.\n";

  assert(openHash.getSize() == testSize &&
         "Hash table size should match the number of inserted elements");

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

  std::cout << "All tests passed successfully." << std::endl;
  return 0;
}

int testChainingHash(size_t testSize) {
  Chaining<int, std::string> chainingHash;
  auto start = std::chrono::high_resolution_clock::now();
  for (size_t i = 0; i < testSize; ++i) {
    chainingHash.insert(i, "Value_" + std::to_string(i));
  }
  auto insertEnd = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> insertDuration = insertEnd - start;
  std::cout << "Insertion of " << testSize
            << " elements in a chaining hashtable took "
            << insertDuration.count() << " seconds.\n";

  assert(chainingHash.getSize() == testSize &&
         "Hash table size should match the number of inserted elements");

  auto retrieveStart = std::chrono::high_resolution_clock::now();
  for (size_t i = 0; i < testSize; ++i) {
    std::string expectedValue = "Value_" + std::to_string(i);
    assert(chainingHash.get(i) == expectedValue &&
           "Retrieved value should match the inserted value");
  }
  auto retrieveEnd = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> retrieveDuration = retrieveEnd - retrieveStart;
  std::cout << "Retrieval of " << testSize
            << " elements in a chaining hashtable took "
            << retrieveDuration.count() << " seconds.\n";

  std::cout << "All tests passed successfully." << std::endl;
  return 0;
}

int testLinkedList(size_t testSize) {
  LinkedList<std::pair<int, std::string>> linkedList;

  auto insertStart = std::chrono::high_resolution_clock::now();
  for (int i = 0; i < (int) testSize; ++i) {
    linkedList.pushBack({i, "Value_" + std::to_string(i)});
  }
  auto insertEnd = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> insertDuration = insertEnd - insertStart;
  std::cout << "Insertion of " << testSize
            << " elements in the linked list took " << insertDuration.count()
            << " seconds.\n";

  assert(linkedList.size() == static_cast<size_t>(testSize) &&
         "Linked list size should match the number of inserted elements");

  auto retrieveStart = std::chrono::high_resolution_clock::now();
  for (int i = 0; i < (int) testSize; ++i) {
    auto frontPair = linkedList.front();
    assert(frontPair.first == i &&
           "Retrieved key should match the inserted key");
    std::string expectedValue = "Value_" + std::to_string(i);
    assert(frontPair.second == expectedValue &&
           "Retrieved value should match the inserted value");
    linkedList.popFront();
  }
  auto retrieveEnd = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> retrieveDuration = retrieveEnd - retrieveStart;
  std::cout << "Retrieval of " << testSize
            << " elements in the linked list took " << retrieveDuration.count()
            << " seconds.\n";

  assert(linkedList.isEmpty() &&
         "Linked list should be empty after popping all elements");
  std::cout << "All tests passed successfully.\n";
  return 0;
}

int main() {
  testOpenAddressing(1'000'000);
  testChainingHash(1'000'000);
  testLinkedList(1'000'000);
  return 0;
}