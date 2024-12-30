// Copyright Ben Roberts 2024

#pragma once

#include "linked_list.h" // For linked lists
#include <functional>    // For std::hash
#include <stdexcept>     // For std::exception
#include <vector>        // For std::vector


template <typename KeyType, typename ValueType> class ChainingLinkedHash {
private:
  struct Entry {
    KeyType key;
    ValueType value;
    Entry(const KeyType &k, const ValueType &v) : key(k), value(v) {}
  };

  std::vector<LinkedList<Entry>> table_;
  size_t size_;
  float load_factor_;

  size_t getCapacity() const { return table_.size(); }

  size_t hash(const KeyType &key) const {
    return std::hash<KeyType>{}(key) % getCapacity();
  }

  void rehash(size_t new_capacity) {
    auto old_table = table_;
    table_ = std::vector<LinkedList<Entry>>(new_capacity);
    size_ = 0;

    for (const auto &list : old_table) {
      for (const auto &entry : list) {
        insert(entry.key, entry.value);
      }
    }
  }

public:
  explicit ChainingLinkedHash(size_t capacity = 8, float load_factor = 2.0)
      : table_(capacity), size_(0), load_factor_(load_factor) {}

  void insert(const KeyType &key, const ValueType &value) {
    if (static_cast<float>(size_ + 1) / getCapacity() > load_factor_) {
      rehash(getCapacity() * 2);
      /* The number of copies per element is an amortized constant cost.
      For pushes N, we are copying at increments: 1->2, 2->4, 4->8...
      Therefore, reallocation happens at 1,2,4,...,2^k for 2^k <= N < 2^k+1
      Total copy cost is 1 + 2 + 4 + ... + 2^k = 2^k+1 - 1 <= 2N - 1
      Finally, amortized cost is no greater than 2N - 1 / N < 2
      */
    }
    size_t hash_index = hash(key);
    table_[hash_index].pushBack({key, value});
    size_++;
  }

  ValueType get(const KeyType &key) const {
    size_t hash_index = hash(key);
    for (const auto &entry : table_[hash_index]) {
      if (entry.key == key) {
        return entry.value;
      }
    }
    throw std::runtime_error("Element is not in the table");
  }

  size_t getSize() { return size_; }
};