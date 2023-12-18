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
    const_iterator(const T** p, const uint32_t idx) : pos_(p), index_(idx) {}

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
    iterator(const T** p, const uint32_t idx) : const_iterator(p, idx) {}

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

  iterator begin() { return iterator(map_[0]); }

  const_iterator cbegin() const { return const_iterator(map_[0]); }

  iterator end() { return iterator(map_[BLOCK_SIZE / size_]); }

  const_iterator cend() const {
    return const_iterator(map_[BLOCK_SIZE / size_]);
  }

  uint32_t size() const { return size_; }

  bool empty() const { return size_ == 0; }

  void clear() const {}

  T& operator[](const uint32_t n) {
    return map_[BLOCK_SIZE / n][BLOCK_SIZE % n];
  }

  T& front() { return (*begin()); }

  const T& front() const { return (*cbegin()); }

  T& back() { return (*end()); }

  const T& back() const { return (*cend()); }

  void push_back(const T& elem) { insert(cend(), elem); }

  void pop_back() { erase(--end()); }

  iterator insert(const_iterator pos, const T& elem) {
    ++size_;
    return iterator(map_[0]);
  }

  iterator erase(const_iterator pos) {
    --size_;
    return iterator(map_[0]);
  }

 private:
  void init() {
    size_ = 0;
    block_count_ = 0;
    map_ = new T*[1];
    map_[1] = new T[BLOCK_SIZE];
  }

 private:
  T** map_;
  uint32_t size_;
  uint32_t block_count_;
};  // deque
}  // namespace ds
#endif