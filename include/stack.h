#ifndef STACK_H
#define STACK_H

#include "list.h"

namespace ds {
template <typename T, typename sequence = ds::list<T>>
class stack final {
 public:
  stack() = default;
  ~stack() = default;

 public:
  // element access
  T& top() { return container.back(); }

  // capacity
  bool empty() const { return container.empty(); }

  uint32_t size() const { return container.size(); }

  // modifiers
  void push(const T& value) { container.push_back(value); }

  void pop() { container.pop_back(); }

 private:
  sequence container;
};  // stack
}  // namespace ds
#endif