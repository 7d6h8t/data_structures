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
    friend class vector<T>;

   protected:
    const_iterator(T* p) : pos_(p) {}

   public:
    const_iterator() : pos_(nullptr) {}

    const T& operator*() const { return *pos_; }

    const_iterator operator+(int n) {
      pos_ += n;
      return *this;
    }

    const_iterator operator-(int n) {
      pos_ -= n;
      return *this;
    }

    bool operator==(const const_iterator& rhs) const {
      return (pos_ == rhs.pos_);
    }

    bool operator!=(const const_iterator& rhs) const {
      return (pos_ != rhs.pos_);
    }

   protected:
    T* pos_;
  };  // const_iterator

  class iterator : public const_iterator {
    friend class vector<T>;

   protected:
    iterator(T* p) : const_iterator(p) {}

   public:
    iterator() {}

    T& operator*() { return *(this->pos_); }

    iterator& operator++() {
      ++(this->pos_);
      return *this;
    }

    iterator operator++(int) {
      iterator temp = *this;
      ++(*this);
      return temp;
    }

    iterator& operator--() {
      --(this->pos_);
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
  vector(const types&... args) {
    init();
    reserve(sizeof...(args));
    (push_back(args), ...);
  }

  vector(const vector<T>& rhs) {
    size_ = rhs.size_;
    reserve(rhs.capacity_);
    for (const auto& elem : rhs) push_back(elem);
  }

  vector(vector<T>&& rhs) {
    size_ = std::move(rhs.size_);
    reserve(std::move(rhs.capacity_));
    for (const auto& elem : rhs) push_back(std::move(elem));
  }

  ~vector() {
    clear();
    if (head_ != nullptr) delete[] head_;
  }

  vector& operator=(const vector<T>& rhs) {
    clear();
    size_ = rhs.size_;
    reserve(rhs.capacity_);
    for (const auto& elem : rhs) push_back(elem);

    return *this;
  }

  vector& operator=(vector<T>&& rhs) {
    clear();
    size_ = std::move(rhs.size_);
    reserve(std::move(rhs.capacity_));
    for (const auto& elem : rhs) push_back(std::move(elem));

    return *this;
  }

  iterator begin() { return iterator(head_); }

  const_iterator cbegin() const { return const_iterator(head_); }

  iterator end() { return iterator(head_ + size_); }

  const_iterator cend() const { return const_iterator(head_ + size_); }

  uint32_t size() const { return size_; }

  bool empty() const { return size_ == 0; }

  void clear() {
    while (!empty()) pop_back();
  }

  T& at(const uint32_t n) { return head_[n]; }

  const T& at(const uint32_t n) const { return head_[n]; }

  T& operator[](const uint32_t n) { return head_[n]; }

  T& front() { return (*begin()); }

  const T& front() const { return (*cbegin()); }

  T& back() { return (*--end()); }

  const T& back() const { return (*--cend()); }

  void push_back(const T& elem) { insert(cend(), elem); }

  void push_back(T&& elem) { insert(cend(), std::move(elem)); }

  void pop_back() { erase(--end()); }

  iterator insert(const_iterator pos, const T& elem) {
    uint32_t curr = pos.pos_ - head_;
    if (size_ == capacity_) reserve((size_ + 1) * 2);

    for (uint32_t i = curr; i < size_; ++i) head_[i + 1] = head_[i];

    head_[curr] = elem;
    ++size_;
    return iterator(head_ + curr);
  }

  iterator erase(const_iterator pos) {
    uint32_t curr = pos.pos_ - head_;

    for (uint32_t i = curr; i < size_; ++i) head_[i] = head_[i + 1];

    --size_;
    return iterator(head_ + curr);
  }

  void reserve(const uint32_t n) {
    if (capacity_ >= n) return;

    capacity_ = n;
    realloc(capacity_);
  }

 private:
  void init() {
    size_ = 0;
    capacity_ = 0;
    head_ = nullptr;
  }

  void realloc(uint32_t n) {
    T* temp = new T[n];
    for (uint32_t i = 0; i < size_; ++i) temp[i] = head_[i];

    if (head_ != nullptr) delete[] head_;

    head_ = temp;
  }

 private:
  uint32_t size_;
  uint32_t capacity_;
  T* head_;
};  // vector
}  // namespace ds
#endif