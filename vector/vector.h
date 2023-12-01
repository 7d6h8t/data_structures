#include <concepts>

namespace ds {
template <typename T>
class vector_iterator {
 private:
  using value_type = T;
  using size_type = std::size_t;
  using reference = T&;
  using pointer = T*;
  using self = vector_iterator<T>;

 public:
  vector_iterator() noexcept : current_() {}
  vector_iterator(const T& i) noexcept : current_(i) {}
  vector_iterator(const vector_iterator& rhs) noexcept : current_(rhs.base()) {}

 public:
  reference operator*() { return *current_; }

  pointer operator->() { return current_; }

  self& operator++() {
    ++current_;
    return *this;
  }

  self operator++(int) { return self(current_++); }

  self& operator--() {
    --current_;
    return *this;
  }

  self operator--(int) { return self(current_--); }

  reference operator[](const size_type n) { return current_[n]; }

  self& operator+=(const size_type n) {
    current_ += n;
    return *this;
  }

  self operator+(const size_type n) { return self(current_ + n); }

  self& operator-=(const size_type n) {
    current_ -= n;
    return *this;
  }

  self operator-(const size_type n) { return self(current_ - n); }

  bool operator==(const self& rhs) const { return current_ == rhs.base(); }

  bool operator!=(const self& rhs) const { return !(*this == rhs); }

  const reference& base() const noexcept { return current_; }

 private:
  pointer current_;
};

template <typename T>
class vector {
 public:
  using value_type = T;
  using size_type = std::size_t;
  using pointer = T*;
  using reference = T&;
  using const_reference = const T&;
  using iterator = vector_iterator<T>;
  using const_iterator = const iterator;

 public:
  template <typename... types>
  requires(std::same_as<T, types>&&...) vector(const types&... args)
      : size_(0), capacity_(0) {
    reserve(sizeof...(args));
    (push_back(args), ...);
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

  const_reference operator[](const size_type pos) const { return at(pos); }

  // capacity
  bool empty() const noexcept { return size_ == 0; }

  bool size() const noexcept { return size_; }

  void reserve(const size_type new_cap) {
    if (new_cap > capacity_)
      realloc(new_cap);
  }

  size_type capacity() const { return capacity_; }

  // modifiers
  void push_back(const value_type& value) {
    if (size_ >= capacity_)
      realloc(capacity_ * 2);

    head_[size_++] = value;
  }

 private:
  void realloc(const size_type& n) {
    capacity_ = n;
    value_type* temp = new value_type[capacity_];

    for (size_type i = 0; i < size_; ++i)
      temp[i] = head_[i];

    delete[] head_;
    head_ = temp;
  }

 private:
  size_type size_;
  size_type capacity_;
  iterator head_;
};
}  // namespace ds