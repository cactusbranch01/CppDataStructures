// Copyright Ben Roberts 2024

#include "linked_list.h"
#include <stdexcept>

using namespace std;

template <typename KeyType, typename ValueType> class ChainingLinkedHash {
public:
  explicit ChainingLinkedHash(size_t capacity = 8, float load_factor = 2.0)
      : table_(capacity), size_(0), load_factor_(load_factor) {}

  void insert(const KeyType &key, const ValueType &value) {
    if (static_cast<float>(size_ + 1) / getCapacity() > load_factor_) {
      rehash();
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
    throw runtime_error("Element is not in the table");
  }

  size_t getSize() { return size_; }

private:
  struct Entry {
    KeyType key;
    ValueType value;

    Entry(const KeyType &k, const ValueType &v) : key(k), value(v) {}
  };

  vector<LinkedList<Entry>> table_;
  size_t size_;
  float load_factor_;

  size_t getCapacity() const { return table_.size(); }

  size_t hash(const KeyType &key) const {
    return std::hash<KeyType>{}(key) % getCapacity();
  }

  void rehash() {
    auto old_table = table_;
    table_ = vector<LinkedList<Entry>>(getCapacity() * 2);
    size_ = 0;

    for (const auto &list : old_table) {
      for (const auto &entry : list) {
        insert(entry.key, entry.value);
      }
    }
  }
};