#ifndef DEQUE_H
#define DEQUE_H

#include <concepts>
#include <cstdint>
#include <stdexcept>

namespace ds {
template <typename T, uint32_t BLOCK_SIZE = 5>
class deque final {
 public:
  class const_iterator {
    friend class deque<T>;

   protected:
    const_iterator(const deque<T>* deq, const uint32_t i, const uint32_t j)
        : deq_(deq), block_index_(i), index_(j) {}

   public:
    const_iterator() : deq_(nullptr), block_index_(0), index_(0) {}

    const T& operator*() const { return deq_->map_[block_index_][index_]; }

    const_iterator operator+(int n) {
      const_iterator temp = *this;
      uint32_t total = (block_index_ * BLOCK_SIZE) + index_;

      temp.block_index_ = (total + n) / BLOCK_SIZE;
      temp.index_ = (total + n) % BLOCK_SIZE;

      return temp;
    }

    const_iterator operator-(int n) {
      const_iterator temp = *this;
      uint32_t total = (block_index_ * BLOCK_SIZE) + index_;

      if (n > total) throw std::out_of_range("access violation!");

      temp.block_index_ = (total - n) / BLOCK_SIZE;
      temp.index_ = (total - n) % BLOCK_SIZE;

      return temp;
    }

    bool operator==(const const_iterator& rhs) const {
      return (deq_ == rhs.deq_) && (block_index_ == rhs.block_index_) &&
             (index_ == rhs.index_);
    }

    bool operator!=(const const_iterator& rhs) const { return !(*this == rhs); }

   protected:
    const deque<T>* deq_;
    uint32_t block_index_;
    uint32_t index_;
  };  // const_iterator

  class iterator : public const_iterator {
    friend class deque<T>;

   protected:
    iterator(deque<T>* deq, const uint32_t i, const uint32_t j)
        : const_iterator(deq, i, j) {}

   public:
    iterator() {}

    T& operator*() {
      return this->deq_->map_[this->block_index_][this->index_];
    }

    iterator operator+(int n) {
        iterator temp = *this;
        uint32_t total = (this->block_index_ * BLOCK_SIZE) + this->index_;

        temp.block_index_ = (total + n) / BLOCK_SIZE;
        temp.index_ = (total + n) % BLOCK_SIZE;

        return temp;
    }

    iterator operator-(int n) {
        iterator temp = *this;
        uint32_t total = (this->block_index_ * BLOCK_SIZE) + this->index_;

        if (n > total) throw std::out_of_range("access violation!");

        temp.block_index_ = (total - n) / BLOCK_SIZE;
        temp.index_ = (total - n) % BLOCK_SIZE;

        return temp;
    }

    iterator& operator++() {
      if (++(this->index_) == BLOCK_SIZE) {
        ++(this->block_index_);
        (this->index_) = 0;
      }
      return *this;
    }

    iterator operator++(int) {
      iterator temp = *this;
      ++(*this);
      return temp;
    }

    iterator& operator--() {
      if ((this->index_) == 0) {
        --(this->block_index_);
        (this->index_) = BLOCK_SIZE - 1;
      } else {
        --(this->index_);
      }
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

  iterator begin() { return iterator(this, begin_block_, begin_index_); }

  const_iterator cbegin() const {
    return const_iterator(this, begin_block_, begin_index_);
  }

  iterator end() { return iterator(this, end_block_, end_index_); }

  const_iterator cend() const {
    return const_iterator(this, end_block_, end_index_);
  }

  uint32_t size() const {
      return size_;
  }

  bool empty() const { return size() == 0; }

  void clear() {
    while (!empty()) pop_back();
  }

  T& operator[](const uint32_t n) { return *(begin() + n); }

  T& front() { return (*begin()); }

  const T& front() const { return (*cbegin()); }

  T& back() { return *(--end()); }

  const T& back() const { return *(--cend()); }

  void push_back(const T& elem) { insert(cend(), elem); }

  void pop_back() { erase(--end()); }

  void push_front(const T& elem) { insert(cbegin(), elem); }

  void pop_front() { erase(cbegin()); }

  iterator insert(const_iterator pos, const T& elem) {
    if (pos == cbegin()) {
      if (pos.block_index_ == 0 && pos.index_ == 0)
        realloc_front((capacity_ * 2) + 3);

      iterator itr = --begin();
      *itr = elem;
      begin_block_ = itr.block_index_;
      begin_index_ = itr.index_;

      return itr;
    }

    if (end_block_ == capacity_ && end_index_ == BLOCK_SIZE - 1)
      realloc_back((capacity_ * 2) + 3);

    iterator itr{this, pos.block_index_, pos.index_};
    for (auto it = itr; it != end(); ++it) *(it + 1) = *it;

    *itr = elem;
    if (++end_index_ == BLOCK_SIZE) {
    ++end_block_;
    end_index_ = 0;
    }

    return itr;
  }

  iterator erase(const_iterator pos) {
    iterator itr{this, pos.block_index_, pos.index_};

    for (auto it = itr; it != end(); ++it) *it = *(it + 1);

    return itr;
  }

 private:
  void init() {
    size_ = 0;
    begin_index_ = end_index_ = 0;
    begin_block_ = end_block_ = 0;
    map_ = nullptr;
    capacity_ = 0;
  }

  void realloc_front(const uint32_t n) {
    if (capacity_ >= n) return;

    T** temp = new T*[n];
    for (uint32_t i = 0; i < n; ++i) temp[i] = new T[BLOCK_SIZE];

    uint32_t new_alloc_count = n - capacity_;

    for (uint32_t i = begin_block_; i < end_block_; ++i)
      temp[new_alloc_count + i - 1] = map_[i];

    begin_block_ += new_alloc_count - 1;
    end_block_ += new_alloc_count - 1;
    capacity_ = n;

    if (map_ != nullptr) delete[] map_;
    map_ = temp;
  }

  void realloc_back(const uint32_t n) {
    if (capacity_ >= n) return;
    capacity_ = n;

    T** temp = new T*[n];
    for (uint32_t i = 0; i < n; ++i) temp[i] = new T[BLOCK_SIZE];

    for (uint32_t i = begin_block_; i < end_block_; ++i)
      temp[i] = map_[i];

    if (map_ != nullptr) delete[] map_;
    map_ = temp;
  }

 private:
  T** map_;
  uint32_t size_;
  uint32_t begin_block_, end_block_;
  uint32_t begin_index_, end_index_;
  uint32_t capacity_;
};  // deque
}  // namespace ds
#endif