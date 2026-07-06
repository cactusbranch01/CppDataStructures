// Created by Ben Roberts 2024

#pragma once

#include "../list/vector.h" // For Vector
#include <functional>       // For std::hash
#include <stdexcept>        // For std::exception

template <typename KeyType, typename ValueType> class OpenAddressHash {
private:
  struct Entry {
    KeyType key;
    ValueType value;
    bool empty = true;
    bool deleted = false;
  };

  Vector<Entry> table_;
  size_t num_elements_;
  size_t num_deleted_;
  float load_factor_;

  size_t capacity() const { return table_.capacity(); }

  size_t standardHash(const KeyType& key) const {
    return std::hash<KeyType>{}(key) % capacity();
  }

  void rehash(size_t newCapacity) {
    auto old_table = table_;
    table_ = Vector<Entry>(newCapacity);
    num_elements_ = 0;
    num_deleted_ = 0;

    for (const auto& entry : old_table) {
      if (!entry.empty) {
        insert(entry.key, entry.value);
      }
    }
  }

public:
  explicit OpenAddressHash(size_t capacity = 8, float load_factor = 0.5)
      : table_(capacity), num_elements_(0), num_deleted_(0),
        load_factor_(load_factor) {}

  void insert(const KeyType& key, const ValueType& value) {
    if (static_cast<float>(num_elements_ + num_deleted_ + 1) / capacity() >
        load_factor_) {
      rehash(capacity() * 2);
    }

    size_t index = standardHash(key);
    size_t probe = index;
    size_t first_deleted = capacity();

    while (!table_[probe].empty || table_[probe].deleted) {
      if (!table_[probe].empty && table_[probe].key == key) {
        // Update existing key
        table_[probe].value = value;
        return;
      }
      if (table_[probe].deleted && first_deleted == capacity()) {
        first_deleted = probe;
      }
      probe = (probe + 1) % capacity();
      if (probe == index) {
        break;
      }
    }

    size_t target = (first_deleted != capacity()) ? first_deleted : probe;
    table_[target] = {key, value, false, false};
    num_elements_++;
  }

  ValueType get(const KeyType& key) {
    size_t index = standardHash(key);
    size_t probe = index;

    while (!table_[probe].empty || table_[probe].deleted) {
      if (!table_[probe].empty && table_[probe].key == key) {
        return table_[probe].value;
      }
      probe = (probe + 1) % capacity();
      if (probe == index) {
        break; // Searched the entire table
      }
    }
    assert(false && "Key does not exist in the table!");
  }

  bool contains(const KeyType& key) const {
    size_t index = standardHash(key);
    size_t probe = index;

    while (!table_[probe].empty || table_[probe].deleted) {
      if (!table_[probe].empty && table_[probe].key == key) {
        return true;
      }
      probe = (probe + 1) % capacity();
      if (probe == index) {
        break;
      }
    }
    return false;
  }

  bool remove(const KeyType& key) {
    size_t index = standardHash(key);
    size_t probe = index;

    while (!table_[probe].empty || table_[probe].deleted) {
      if (!table_[probe].empty && table_[probe].key == key) {
        table_[probe].empty = true;
        table_[probe].deleted = true;
        num_elements_--;
        num_deleted_++;
        return true;
      }
      probe = (probe + 1) % capacity();
      if (probe == index) {
        break;
      }
    }
    return false;
  }

  size_t size() const { return num_elements_; }
};