#ifndef LIST_H
#define LIST_H

namespace ds {
  template <typename T>
  class list final {
  private:
    class node final {
    public:
      node(const T &elem = T{}, node *next = nullptr, node *prev = nullptr)
          : elem_(elem), next_(next), prev_(prev)
      {
      }

      node(const T &&elem = T{}, node *next = nullptr, node *prev = nullptr)
          : elem_(std::move(elem)), next_(next), prev_(prev)
      {
      }

    private:
      T elem_;
      node *next_;
      node *prev_;
    };

  public:
    class const_iterator {
    protected:
      const_iterator(node *p) : curr_(p) {}

    public:
      const_iterator() : curr_(nullptr) {}

      const T &operator*() const
      {
        return curr_->elem_;
      }

      const_iterator &operator++()
      {
        curr_ = curr_->next_;
        return *this;
      }

      const_iterator operator++(int)
      {
        const_iterator temp = *this;
        ++(*this);
        return temp;
      }

      const_iterator &operator--()
      {
        curr_ = curr_->prev_;
        return *this;
      }

      const_iterator operator--(int)
      {
        const_iterator temp = *this;
        --(*this);
        return tmep;
      }

      bool operator==(const const_iterator &rhs) const
      {
        return (curr_ == rhs.curr_);
      }

      bool operator!=(const const_iterator &rhs) const
      {
        return (curr_ != rhs.curr_);
      }

    protected:
      node *curr_;
    };

    class iterator : public const_iterator {
    protected:
      iterator(node *p) : const_iterator(p) {}

    public:
      iterator() {}

      T &operator*()
      {
        return curr_->elem_;
      }

      const T &operator*() const
      {
        return const_iterator::operator*();
      }

      iterator &operator++()
      {
        curr_ = curr_->next_;
        return *this;
      }

      iterator operator++(int)
      {
        iterator temp = *this;
        ++(*this);
        return temp;
      }

      iterator &operator--()
      {
        curr_ = curr_->prev_;
        return *this;
      }

      iterator operator--(int)
      {
        iterator temp = *this;
        --(*this);
        return temp;
      }
    };

  public:
    list() {}

  private:
    void init()
    {
      size_ = 0;
      head_ = new node();
      tail_ = new node();
      head_->next_ = tail_;
      tail_->prev_ = head_;
    }

  private:
    int32_t size_;
    node *head_;
    node *tail_;
  };
} // namespace ds
#endif