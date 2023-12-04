#include "../list/list.h"

namespace ds {
template <typename T, typename sequence = ds::list<T>>
class queue final {

 private:
  sequence container_;
};
}  // namespace ds