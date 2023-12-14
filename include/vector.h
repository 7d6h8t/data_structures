#ifndef VECTOR_H
#define VECTOR_H

#include <concepts>
#include <cstdint>
#include <utility>

namespace ds {
template <typename T>
class vector final {
 public:
  class const_iterator {
   protected:
    const_iterator(T* p) : curr_(p) {}

   public:
    const_iterator() : curr_(nullptr) {}

    const T& operator*() const { return *curr_; }

    const_iterator operator+(int n) {
      curr_ += n;
      return *this;
    }

    const_iterator operator-(int n) {
      curr_ -= n;
      return *this;
    }

    bool operator==(const const_iterator& rhs) const {
      return (curr_ == rhs.curr_);
    }

    bool operator!=(const const_iterator& rhs) const {
      return (curr_ != rhs.curr_);
    }

   protected:
    T* curr_;
  };  // const_iterator

  class iterator : public const_iterator {
   protected:
    iterator(T* p) : const_iterator(p) {}

   public:
    iterator() {}

    iterator& operator++() {
      ++curr_;
      return *this;
    }

    iterator operator++(int) {
      iterator temp = *this;
      ++(*this);
      return temp;
    }

    iterator& operator--() {
      --curr_;
      return *this;
    }

    iterator operator--(int) {
      iterator temp = *this;
      --(*this);
      return temp;
    }
  };  // iterator

 public:
  vector() { init(); }

  template <typename... types>
    requires(std::same_as<T, types> && ...)
  vector(const types&... ars) {}

  iterator begin() { return iterator(head_); }

  const_iterator cbegin() const { return const_iterator(head_); }

  iterator end() { return iterator(head_ + size_); }

  const_iterator cend() const { return const_iterator(head_ + size_); }

  uint32_t size() const { return size_; }

  bool empty() const { return size_ == 0; }

  iterator insert(const_iterator pos, const T& elem) {
    if (size_ == capacity_) realloc(size_ * 2);

    ++size_;
  }

 private:
  void init() {
    size_ = 0;
    capacity_ = 0;
    head_ = nullptr;
  }

  void realloc(uint32_t n) {
    capacity_ = n;
    T* temp = new T[n];
    for (int i = 0; i < size_; ++i) T[i] = head_[i];

    delete[] head_;
    head_ = temp;
  }

 private:
  uint32_t size_;
  uint32_t capacity_;
  T* head_;
};  // vector
}  // namespace ds
#endif