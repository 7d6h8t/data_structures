#ifndef DEQUE_H
#define DEQUE_H

#include <concepts>
#include <cstdint>

namespace ds {
template <typename T, uint32_t BlockSize = 5>
class deque final {
 public:
  class const_iterator {
    friend class deque<T>;

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

    bool operator!=(const const_iterator& rhs) const { return !(*this == rhs); }

   protected:
    T* pos_;
    uint32_t block_index_;
  };  // const_iterator

  class iterator : public const_iterator {
    friend class deque<T>;

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
  deque() { init(); }

  template <typename... types>
    requires(std::same_as<T, types> && ...)
  deque(const types&... args) {}

  ~deque() {}

  iterator begin() { return iterator(map_[0]); }

  const_iterator cbegin() const { return const_iterator(map_[0]); }

  iterator end() { return iterator(map_[BlockSize / size_]); }

  const_iterator cend() const {
    return const_iterator(map_[BlockSize / size_]);
  }

  uint32_t size() const { return size_; }

  bool empty() const { return size_ == 0; }

  void clear() const {}

  T& operator[](const uint32_t n) { return map_[BlockSize / n][BlockSize % n]; }

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
    map_ = nullptr;
  }

 private:
  T** map_;
  uint32_t size_;
};  // deque
}  // namespace ds
#endif