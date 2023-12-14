#ifndef QUEUE_H
#define QUEUE_H

#include "list.h"

namespace ds {
template <typename T, typename sequence = ds::list<T>>
class queue final {
 public:
  queue() = default;
  ~queue() = default;

 public:
  // element access
  T& front() { return container_.front(); }

  T& back() { return container_.back(); }

  // capacity
  bool empty() const { return container_.empty(); }

  uint32_t size() const { return container_.size(); }

  // modifiers
  void push(const T& value) { container_.push_back(value); }

  void pop() { container_.pop_front(); }

 private:
  sequence container_;
};  // queue
}  // namespace ds
#endif