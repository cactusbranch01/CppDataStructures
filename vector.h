// Copyright Ben Roberts 2024

#pragma once

#include <iterator>

template <typename ValueType> class Vector {
private:
  size_t capacity_;
  size_t size_;
  ValueType *array_;

public:
  // Constructors
  Vector() : capacity_(0), size_(0), array_(nullptr) {}

  explicit Vector(size_t initial_capacity)
      : capacity_(initial_capacity), size_(initial_capacity), array_(nullptr) {
    if (capacity_ > 0) {
      array_ = new ValueType[capacity_];
    }
  }

  // Init-list constructor
  Vector(std::initializer_list<ValueType> init)
      : capacity_(init.size()), size_(init.size()), array_(nullptr) {
    if (capacity_ > 0) {
      array_ = new ValueType[capacity_];
      size_t idx = 0;
      for (const auto &val : init) {
        array_[idx++] = val;
      }
    }
  }

  // Copy constructor
  Vector(const Vector &other) : capacity_(other.capacity_), size_(other.size_) {
    if (capacity_ > 0) {
      array_ = new ValueType[capacity_];
      for (size_t i = 0; i < size_; i++) {
        array_[i] = other.array_[i];
      }
    } else {
      array_ = nullptr;
    }
  }

  // Move constructor
  Vector(Vector &&other) noexcept
      : capacity_(other.capacity_), size_(other.size_), array_(other.array_) {
    other.size_ = 0;
    other.capacity_ = 0;
    other.array_ = nullptr;
  }

  // Copy assignment
  Vector &operator=(const Vector &other) noexcept {
    if (this != &other) {
      // If allocated capacity is smaller than other's size, re-allocate
      if (capacity_ < other.size_) {
        delete[] array_;
        array_ = new ValueType[other.capacity_];
        capacity_ = other.capacity_;
      }
      // Copy over the size_ elements
      size_ = other.size_;
      for (size_t i = 0; i < size_; ++i) {
        array_[i] = other.array_[i];
      }
    }
    return *this;
  }

  // Move assignment
  Vector &operator=(Vector &&other) noexcept {
    if (this != &other) {
      delete[] array_;
      capacity_ = other.capacity_;
      size_ = other.size_;
      array_ = other.array_;
      // Null out other's data
      other.capacity_ = 0;
      other.size_ = 0;
      other.array_ = nullptr;
    }
    return *this;
  }

  // Destructor
  ~Vector() { delete[] array_; }

  void clear() { size_ = 0; }

  size_t capacity() const noexcept { return capacity_; }

  size_t size() const noexcept { return size_; }

  bool empty() const noexcept { return size_ == 0; }

  void push_back(const ValueType &value) {
    if (size_ == capacity_) {
      reserve(capacity_ == 0 ? 8 : 2 * capacity_);
    }
    array_[size_++] = value;
  }

  void push_back(ValueType &&value) {
    if (size_ == capacity_) {
      reserve(capacity_ == 0 ? 8 : 2 * capacity_);
    }
    array_[size_++] = std::move(value);
  }

  void pop_back() {
    if (size_ > 0) {
      size_--;
    }
  }

  ValueType &front() { return array_[0]; }

  const ValueType &front() const { return array_[0]; }

  ValueType &back() { return array_[size_ - 1]; }

  const ValueType &back() const { return array_[size_ - 1]; }

  ValueType &operator[](size_t i) { return array_[i]; }

  const ValueType &operator[](size_t i) const { return array_[i]; }

  void reserve(size_t new_cap) {
    if (new_cap > capacity_) {
      ValueType *new_data = new ValueType[new_cap];
      for (size_t i = 0; i < capacity_; ++i) {
        new_data[i] = std::move(array_[i]);
      }
      delete[] array_;
      array_ = new_data;
      capacity_ = new_cap;
    }
  }

  void resize(size_t count) {
    if (count < size_) {
      for (size_t i = size_; i < count; i++) {
        array_[i].~ValueType();
      }
      size_ = count;
    } else if (count > size_) {
      if (count > capacity_) {
        reserve(count);
      }
      for (size_t i = size_; i < count; i++) {
        array_[i] = ValueType();
      }
      size_ = count;
    }
  }

  void resize(size_t count, const ValueType &value) {
    if (count < size_) {
      for (size_t i = size_; i < count; i++) {
        array_[i].~ValueType();
      }
      size_ = count;
    } else if (count > size_) {
      if (count > capacity_) {
        reserve(count);
      }
      for (size_t i = size_; i < count; i++) {
        array_[i] = std::copy(value);
      }
      size_ = count;
    }
  }

  // Non-const iterator
  class Iterator {
  private:
    ValueType *ptr_;

  public:
    explicit Iterator(ValueType *p) : ptr_(p) {}
    ValueType &operator*() const { return *ptr_; }
    ValueType *operator->() const { return ptr_; }
    Iterator &operator++() {
      ++ptr_;
      return *this;
    }
    Iterator operator++(int) {
      Iterator tmp = *this;
      ++(*this);
      return tmp;
    }
    bool operator==(const Iterator &other) const { return ptr_ == other.ptr_; }
    bool operator!=(const Iterator &other) const { return !(*this == other); }
  };

  // Const iterator
  class ConstIterator {
  private:
    const ValueType *ptr_;

  public:
    explicit ConstIterator(const ValueType *p) : ptr_(p) {}
    const ValueType &operator*() const { return *ptr_; }
    const ValueType *operator->() const { return ptr_; }
    ConstIterator &operator++() {
      ++ptr_;
      return *this;
    }
    ConstIterator operator++(int) {
      ConstIterator tmp = *this;
      ++(*this);
      return tmp;
    }
    bool operator==(const ConstIterator &other) const {
      return ptr_ == other.ptr_;
    }
    bool operator!=(const ConstIterator &other) const {
      return !(*this == other);
    }
  };

  // Overloads for normal iteration
  Iterator begin() { return Iterator(array_); }
  Iterator end() { return Iterator(array_ + size_); }

  // Overloads for const iteration
  ConstIterator begin() const { return ConstIterator(array_); }
  ConstIterator end() const { return ConstIterator(array_ + size_); }
};