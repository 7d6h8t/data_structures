#include <concepts>

namespace ds {
template <typename T>
class vector {
 public:
  using value_type = T;
  using size_type = std::size_t;
  using pointer = T*;
  using reference = T&;
  using const_reference = const T&;

 public:
  template <typename... types>
  requires(std::same_as<T, types>&&...) vector(const types&... args) {
    size_ = sizeof...(args);
    capacity_ = size_;
    alloc();
  }

  ~vector() {
    size_ = 0;
    capacity_ = 0;
    if (head_ != nullptr) {
      delete[] head_;
      head_ = nullptr;
    }
  }

 public:
  // element access
  reference at(const size_type pos) { return *(head_ + pos); }

  const_reference at(const size_type pos) const { return *(head_ + pos); }

  reference operator[](const size_type pos) { return at(pos); }

  const_reference operator[](const size_type pos) { return at(pos); }

  // capacity
  void reserve(const size_type new_cap) {
    if (new_cap <= capacity_)
      return;

    capacity_ = new_cap;
  }

  size_type capacity() const { return capacity_; }

 private:
  void alloc() {
    if (head_ != nullptr || capacity_ == 0)
      return;

    head_ = new value_type[capacity_];
  }

  void realloc() {
    capacity_ *= 2;

    value_type* temp = new value_type[capacity_];

    for (size_type i = 0; i < size_; ++i)
      temp[i] = head_[i];

    delete[] head_;
    head_ = temp;
  }

 private:
  size_type size_;
  size_type capacity_;
  value_type* head_;
};
}  // namespace ds