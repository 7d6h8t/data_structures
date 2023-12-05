#include <concepts>

namespace ds {
  template <typename T>
  class vector_iterator
  {
  private:
    using value_type = T;
    using size_type = std::size_t;
    using reference = T &;
    using pointer = T *;
    using self = vector_iterator<T>;

  public:
    vector_iterator() noexcept : current_() {}
    vector_iterator(const pointer p) noexcept : current_(p) {}
    vector_iterator(const vector_iterator &rhs) noexcept : current_(rhs.base())
    {
    }

  public:
    reference operator*()
    {
      return *current_;
    }

    pointer operator->()
    {
      return current_;
    }

    self &operator++()
    {
      ++current_;
      return *this;
    }

    self operator++(int)
    {
      return self(current_++);
    }

    self &operator--()
    {
      --current_;
      return *this;
    }

    self operator--(int)
    {
      return self(current_--);
    }

    reference operator[](const size_type n)
    {
      return current_[n];
    }

    self &operator+=(const size_type n)
    {
      current_ += n;
      return *this;
    }

    self operator+(const size_type n)
    {
      return self(current_ + n);
    }

    self &operator-=(const size_type n)
    {
      current_ -= n;
      return *this;
    }

    self operator-(const size_type n)
    {
      return self(current_ - n);
    }

    bool operator==(const self &rhs) const
    {
      return current_ == rhs.base();
    }

    bool operator!=(const self &rhs) const
    {
      return !(*this == rhs);
    }

    const pointer &base() const noexcept
    {
      return current_;
    }

  private:
    pointer current_;
  };

  template <typename T>
  class vector
  {
  public:
    using value_type = T;
    using size_type = std::size_t;
    using pointer = T *;
    using reference = T &;
    using const_reference = const T &;
    using iterator = vector_iterator<T>;
    using const_iterator = const iterator;

  public:
    template <typename... types>
      requires(std::same_as<T, types> && ...)
    vector(const types &...args) : size_(0), capacity_(0)
    {
      reserve(sizeof...(args));
      (push_back(args), ...);
    }

    ~vector()
    {
      size_ = 0;
      capacity_ = 0;
      if (head_.base() != nullptr) {
        delete[] head_.base();
      }
    }

  public:
    // element access
    reference at(const size_type pos)
    {
      return *(head_ + pos);
    }

    const_reference at(const size_type pos) const
    {
      return *(head_ + pos);
    }

    reference operator[](const size_type pos)
    {
      return at(pos);
    }

    const_reference operator[](const size_type pos) const
    {
      return at(pos);
    }

    reference front()
    {
      return *head_;
    }

    const_reference front() const
    {
      return *head_;
    }

    reference back()
    {
      return *(head_ + size_);
    }

    const_reference back() const
    {
      return *(head_ + size_);
    }

    // iterators
    iterator begin() noexcept
    {
      return head_;
    }

    const_iterator cbgin() const noexcept
    {
      return head_;
    }

    iterator end() noexcept
    {
      return iterator(head_ + size_);
    }

    const_iterator cend() const noexcept
    {
      return const_iterator(head_ + size_);
    }

    // capacity
    bool empty() const noexcept
    {
      return size_ == 0;
    }

    bool size() const noexcept
    {
      return size_;
    }

    void reserve(const size_type new_cap)
    {
      if (new_cap > capacity_)
        realloc(new_cap);
    }

    size_type capacity() const
    {
      return capacity_;
    }

    // modifiers
    iterator insert(const_iterator pos, const value_type &value)
    {
      size_type index = pos.base() - head_.base();

      if (size_ >= capacity_)
        reserve(capacity_ * 2);

      iterator new_pos = begin() + index;

      for (iterator itr = end(); itr != new_pos; --itr)
        *itr = *(itr - 1);

      *new_pos = value;
      ++size_;
      return new_pos;
    }

    iterator erase(const_iterator pos)
    {
      for (iterator itr = pos; itr != end(); ++itr)
        *itr = *(itr + 1);

      --size_;
      return pos;
    }

    void push_back(const value_type &value)
    {
      insert(end(), value);
    }
    void pop_back()
    {
      erase(end());
    }

  private:
    void realloc(const size_type &n)
    {
      capacity_ = n;
      iterator temp(new value_type[capacity_]);

      for (size_type i = 0; i < size_; ++i)
        temp[i] = head_[i];

      delete[] head_.base();
      head_ = temp;
    }

  private:
    size_type size_;
    size_type capacity_;
    iterator head_;
  };
} // namespace ds