#ifndef LIST_H
#define LIST_H

#include <concepts>
#include <cstdint>
#include <utility>

namespace ds {
template <typename T>
class list final {
 private:
  class node final {
    friend class list<T>;

   public:
    node(const T& elem = T{}, node* next = nullptr, node* prev = nullptr)
        : elem_(elem), next_(next), prev_(prev) {}

   private:
    T elem_;
    node* next_;
    node* prev_;
  };  // node

 public:
  class const_iterator {
    friend class list<T>;

   protected:
    const_iterator(node* p) : curr_(p) {}

   public:
    const_iterator() : curr_(nullptr) {}

    const T& operator*() const { return curr_->elem_; }

    const_iterator& operator++() {
      curr_ = curr_->next_;
      return *this;
    }

    const_iterator operator++(int) {
      const_iterator temp = *this;
      ++(*this);
      return temp;
    }

    const_iterator& operator--() {
      curr_ = curr_->prev_;
      return *this;
    }

    const_iterator operator--(int) {
      const_iterator temp = *this;
      --(*this);
      return temp;
    }

    bool operator==(const const_iterator& rhs) const {
      return (curr_ == rhs.curr_);
    }

    bool operator!=(const const_iterator& rhs) const {
      return (curr_ != rhs.curr_);
    }

   protected:
    node* curr_;
  };  // const_iterator

  class iterator : public const_iterator {
    friend class list<T>;

   protected:
    iterator(node* p) : const_iterator(p) {}

   public:
    iterator() {}

    T& operator*() { return this->curr_->elem_; }

    const T& operator*() const { return const_iterator::operator*(); }

    iterator& operator++() {
      this->curr_ = this->curr_->next_;
      return *this;
    }

    iterator operator++(int) {
      iterator temp = *this;
      ++(*this);
      return temp;
    }

    iterator& operator--() {
      this->curr_ = this->curr_->prev_;
      return *this;
    }

    iterator operator--(int) {
      iterator temp = *this;
      --(*this);
      return temp;
    }
  };  // iterator

 public:
  list() { init(); }

  template <typename... types>
    requires(std::same_as<T, types> && ...)
  list(const types&... args) {
    init();
    (push_back(args), ...);
  }

  list(const list& rhs) {
    init();

    for (const auto& elem : rhs) push_back(elem);
  }

  list(list&& rhs) {
    init();

    for (const auto& elem : rhs) push_back(std::move(elem));
  }

  ~list() {
    clear();
    delete head_;
    delete tail_;
  }

  list& operator=(const list& rhs) {
    clear();

    for (const auto& elem : rhs) push_back(elem);

    return *this;
  }

  list& operator=(list&& rhs) {
    clear();

    for (const auto& elem : rhs) push_back(std::move(elem));

    return *this;
  }

  iterator begin() { return iterator(head_->next_); }

  const_iterator cbegin() const { return const_iterator(head_->next_); }

  iterator end() { return iterator(tail_); }

  const_iterator cend() const { return const_iterator(tail_); }

  uint32_t size() const { return size_; }

  bool empty() const { return size_ == 0; }

  void clear() {
    while (!empty()) pop_front();
  }

  T& front() { return (*begin()); }

  const T& front() const { return (*cbegin()); }

  T& back() { return (*--end()); }

  const T& back() const { return (*--cend()); }

  void push_front(const T& elem) { insert(cbegin(), elem); }

  void push_front(T&& elem) { insert(cbegin(), std::move(elem)); }

  void push_back(const T& elem) { insert(cend(), elem); }

  void push_back(T&& elem) { insert(cend(), std::move(elem)); }

  void pop_front() { erase(begin()); }

  void pop_back() { erase(--end()); }

  iterator insert(const_iterator pos, const T& elem) {
    node* curr = pos.curr_;
    node* new_node = new node(elem, curr, curr->prev_);

    curr->prev_->next_ = new_node;
    curr->prev_ = new_node;
    ++size_;
    return iterator(new_node);
  }

  iterator erase(const_iterator pos) {
    node* curr = pos.curr_;
    iterator return_itr(curr->next_);

    curr->prev_->next_ = curr->next_;
    curr->next_->prev_ = curr->prev_;
    delete curr;
    --size_;
    return return_itr;
  }

 private:
  void init() {
    size_ = 0;
    head_ = new node();
    tail_ = new node();
    head_->next_ = tail_;
    tail_->prev_ = head_;
  }

 private:
  uint32_t size_;
  node* head_;
  node* tail_;
};  // list
}  // namespace ds
#endif