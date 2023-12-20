#ifndef DEQUE_H
#define DEQUE_H

#include <concepts>
#include <cstdint>

namespace ds {
template <typename T, uint32_t BLOCK_SIZE = 5>
class deque final {
 public:
  class const_iterator {
    friend class deque<T>;

   protected:
    const_iterator(T** p, const uint32_t idx) : pos_(p), index_(idx) {}

   public:
    const_iterator() : pos_(nullptr), index_(0) {}

    const T& operator*() const {
      return pos_[index_ / BLOCK_SIZE][index_ % BLOCK_SIZE];
    }

    const_iterator operator+(int n) {
      const_iterator temp = *this;
      temp.index_ += n;
      return temp;
    }

    const_iterator operator-(int n) {
      const_iterator temp = *this;
      temp.index_ -= n;
      return temp;
    }

    bool operator==(const const_iterator& rhs) const {
      return (pos_ == rhs.pos_) && (index_ == rhs.index_);
    }

    bool operator!=(const const_iterator& rhs) const { return !(*this == rhs); }

   protected:
    T** pos_;
    uint32_t index_;
  };  // const_iterator

  class iterator : public const_iterator {
    friend class deque<T>;

   protected:
    iterator(T** p, const uint32_t idx) : const_iterator(p, idx) {}

   public:
    iterator() {}

    T& operator*() {
      return this
          ->pos_[(this->index_ / BLOCK_SIZE)][(this->index_ % BLOCK_SIZE)];
    }

    iterator& operator++() {
      ++(this->index_);
      return *this;
    }

    iterator operator++(int) {
      iterator temp = *this;
      ++(*this);
      return temp;
    }

    iterator& operator--() {
      --(this->index_);
      return *this;
    }

    iterator operator--(int) {
      iterator temp = *this;
      --(*this);
      return temp;
    }
  };  // iterator

 public:
  deque() { init(); }

  template <typename... types>
    requires(std::same_as<T, types> && ...)
  deque(const types&... args) {
    init();
    (push_back(args), ...);
  }

  ~deque() {}

  iterator begin() { return iterator(map_, 0); }

  const_iterator cbegin() const { return const_iterator(map_, 0); }

  iterator end() { return iterator(map_, size_); }

  const_iterator cend() const { return const_iterator(map_, size_); }

  uint32_t size() const { return size_; }

  bool empty() const { return size_ == 0; }

  void clear() {
    while (!empty()) pop_back();
  }

  T& operator[](const uint32_t n) {
    return map_[n / BLOCK_SIZE][n % BLOCK_SIZE];
  }

  T& front() { return (*begin()); }

  const T& front() const { return (*cbegin()); }

  T& back() { return *(--end()); }

  const T& back() const { return *(--cend()); }

  void push_back(const T& elem) { insert(cend(), elem); }

  void pop_back() { erase(--end()); }

  void push_front(const T& elem) { insert(cbegin(), elem); }

  void pop_front() { erase(cbegin()); }

  iterator insert(const_iterator pos, const T& elem) {
    if (size_ == capacity_ * BLOCK_SIZE) realloc((size_ / BLOCK_SIZE) + 1);

    uint32_t index = pos.index_;

    for (uint32_t i = size_; i > index; --i) {
      map_[i / BLOCK_SIZE][i % BLOCK_SIZE] =
          map_[(i - 1) / BLOCK_SIZE][(i - 1) % BLOCK_SIZE];
    }

    map_[index / BLOCK_SIZE][index % BLOCK_SIZE] = elem;
    ++size_;
    return iterator(map_, index);
  }

  iterator erase(const_iterator pos) {
    uint32_t index = pos.index_;

    for (uint32_t i = index; i < size_ - 1; ++i) {
      map_[i / BLOCK_SIZE][i % BLOCK_SIZE] =
          map_[(i + 1) / BLOCK_SIZE][(i + 1) % BLOCK_SIZE];
    }

    --size_;
    return iterator(map_, index);
  }

 private:
  void init() {
    size_ = 0;
    capacity_ = 0;
    map_ = nullptr;
  }

  void realloc(uint32_t n) {
    if (capacity_ >= n) return;

    capacity_ = n;

    T** temp = new T*[capacity_];
    for (uint32_t i = 0; i < capacity_; ++i) temp[i] = new T[BLOCK_SIZE];

    for (uint32_t i = 0; i < size_ / BLOCK_SIZE; ++i) temp[i] = map_[i];

    if (map_ != nullptr) delete[] map_;

    map_ = temp;
  }

 private:
  T** map_;
  uint32_t size_;
  uint32_t capacity_;
};  // deque
}  // namespace ds
#endif