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

  uint32_t size() const { return 1; }

  bool empty() const { return true; }

  void clear() const {}

  T& operator[](const uint32_t n) { return elem_; }

  T& front() { return elem_; }

  const T& front() const { return elem_; }

  T& back() { return elem_; }

  const T& back() const { return elem_; }

  void push_back(const T& elem) {}

  void pop_back() {}

 private:
  void init() {
    size_ = 0;
    chunk_head_ = nullptr;
  }

 private:
  T** chunk_head_;
  uint32_t size_:
};  // deque
}  // namespace ds
#endif