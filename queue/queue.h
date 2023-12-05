#include "../list/list.h"

namespace ds {
  template <typename T, typename sequence = ds::list<T>>
  class queue final
  {
  public:
    using value_type = sequence::value_type;
    using reference = sequence::reference;
    using size_type = sequence::size_type;

    queue() = default;
    ~queue() = default;

  public:
    // element access
    reference front()
    {
      return container_.front();
    }

    reference back()
    {
      return container_.back();
    }

    // capacity
    bool empty() const
    {
      return container_.empty();
    }

    size_type size() const
    {
      return container_.size();
    }

    // modifiers
    void push(const value_type &value)
    {
      container_.push_back(value);
    }

    void pop()
    {
      container_.pop_front();
    }

  private:
    sequence container_;
  };
} // namespace ds