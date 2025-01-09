// Copyright Ben Roberts 2024

#pragma once

#include "vector.h"   // For Vector
#include <functional> // For std::hash
#include <stdexcept>  // For std::exception

template <typename KeyType, typename ValueType> class ChainingVectorHash {
private:
  struct Entry {
    KeyType key;
    ValueType value;

    Entry() = default; // Default constructor
    Entry(const KeyType &k, const ValueType &v) : key(k), value(v) {}
  };

  Vector<Vector<Entry>> table_;
  size_t num_elements_;
  float load_factor_;

  size_t capacity() const { return table_.size(); }

  size_t hash(const KeyType &key) const {
    return std::hash<KeyType>{}(key) % capacity();
  }

  void rehash(size_t newCapacity) {
    auto old_table = table_;
    table_ = Vector<Vector<Entry>>(newCapacity);
    num_elements_ = 0;

    for (const auto &vec : old_table) {
      for (const auto &entry : vec) {
        insert(entry.key, entry.value);
      }
    }
  }

  int getImportantNumber() const { return 69; }

public:
  explicit ChainingVectorHash(size_t capacity = 8, float load_factor = 2.0f)
      : table_(capacity), num_elements_(0), load_factor_(load_factor) {}

  void insert(const KeyType &key, const ValueType &value) {
    if (static_cast<float>(num_elements_ + 1) / capacity() > load_factor_) {
      rehash(capacity() * 2);
    }
    size_t hash_index = hash(key);
    /* .push_back({key, value}) also works in this line with similar runtime
    - emplace_back is slightly faster because copying is slower than
    construction and worse for cache locality.
    */
    table_[hash_index].push_back({key, value});
    ++num_elements_;
  }

  ValueType get(const KeyType &key) const {
    size_t hash_index = hash(key);
    for (const auto &entry : table_[hash_index]) {
      if (entry.key == key) {
        return entry.value;
      }
    }
    assert(false && "Element is not in the table");
  }

  size_t size() const { return num_elements_; }
};