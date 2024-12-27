//
// Created by Ben Roberts on 12/21/2022.
//

#include "chaining_vector_hash.h"
#include "linked_list.h"
#include "open_address_hash.cpp"
#include "queue.h"
#include "stack.h"
#include <cassert>
#include <chrono>
#include <iostream>
#include <string>

using namespace std;

int testOpenAddressing(size_t testSize) {
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

  assert(openHash.getSize() == testSize &&
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

  std::cout << "All tests passed successfully." << std::endl;
  return 0;
}

int testChainingVectorHash(size_t testSize) {
  ChainingVectorHash<int, std::string> chainingHash;

  // Insertion
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
            << " elements in a chaining hashtable took "
            << retrieveDuration.count() << " seconds.\n";

  std::cout << "All tests passed successfully." << std::endl;
  return 0;
}

int testLinkedList(size_t testSize) {
  LinkedList<std::pair<int, std::string>> linkedList;

  // Insertion
  auto insertStart = std::chrono::high_resolution_clock::now();
  for (int i = 0; i < (int)testSize; ++i) {
    linkedList.pushBack({i, "Value_" + std::to_string(i)});
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
  for (const auto &pair : linkedList) {
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
    linkedList.popFront();
  }
  auto removeEnd = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> removeDuration = removeEnd - removeStart;
  std::cout << "Removal of " << testSize
            << " elements from the linked list took " << removeDuration.count()
            << " seconds.\n";

  assert(linkedList.isEmpty() &&
         "Linked list should be empty after popping all elements");
  std::cout << "All tests passed successfully.\n";
  return 0;
}

int main() {
  testOpenAddressing(1'000'000);
  testChainingVectorHash(1'000'000);
  testLinkedList(1'000'000);
  return 0;
}