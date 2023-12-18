#ifndef DEQUE_H
#define DEQUE_H

#include <concepts>
#include <cstdint>

#include "array.h"
#include "list.h"

namespace ds {
template <typename T>
class deque final {
 public:
  class const_iterator {};  // const_iterator

  class iterator : public const_iterator {};  // iterator

 public:
  deque() { init(); }

  template <typename... types>
    requires(std::same_as<T, types> && ...)
  deque(const types&... args) {}

  ~deque() {}

  iterator begin() { return iterator(chunk_head_); }

  const_iterator cbegin() const { return const_iterator(chunk_head_); }

  iterator end() { return iterator(chunk_head_ + size_); }

  const_iterator cend() const { return const_iterator(chunk_head_ + size_); }

  uint32_t size() const { return size_; }

  bool empty() const { return size_ == 0; }

  void clear() const {}

  T& operator[](const uint32_t n) {
    return chunk_head_[chunk_size_ / n][chunk_size_ % n];
  }

  T& front() { return (*begin()); }

  const T& front() const { return (*cbegin()); }

  T& back() { return (*end()); }

  const T& back() const { return (*cend()); }

  void push_back(const T& elem) {}

  void pop_back() {}

  iterator insert(const_iterator pos, const T& elem) {}

  iterator erase(const_iterator pos) {}

 private:
  void init() {
    size_ = 0;
    chunk_head_ = nullptr;
  }

 private:
  T** chunk_head_;
  uint32_t size_;
  static const uint32_t chunk_size_ = 5;
};  // deque
}  // namespace ds
#endif