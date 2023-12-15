#ifndef DEQUE_H
#define DEQUE_H

#include <concepts>
#include <cstdint>

namespace ds {
template <typename T>
class deque final {
 public:
  deque() {}

  template <typename... types>
    requires(std::same_as<T, types> && ...)
  deque(const types&... args) {}

  ~deque() {}

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
  T elem_;
};  // deque
}  // namespace ds
#endif