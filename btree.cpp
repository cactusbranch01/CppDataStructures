// Copyright Ben Roberts 2024

#include <iostream>
#include <vector>

using namespace std;

template <nametype ValueType>

class BTree() {
private:
  struct Entry {
    int key;
    ValueType value;
    bool empty;
  };

  struct BTreeNode {
    vector<Entry> table_;
    size_t num_elements_;
    size_t capacity_;
  };

public:
  explicit BTree() : {}
}