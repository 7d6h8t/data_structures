#include "../list/list.h"

namespace ds {
template <typename T, typename sequence = ds::list<T>>
class stack final {
 public:
  using value_type = sequence::value_type;
  using reference = sequence::reference;
  using size_type = sequence::size_type;

  stack() = default;
  ~stack() = default;

 public:
  // element access
  reference top() { return container.back(); }

  // capacity
  bool empty() const { return container.empty(); }

  size_type size() const { return container.size(); }

  // modifiers
  void pop() { container.pop_back(); }

 private:
  sequence container;
};
}  // namespace ds