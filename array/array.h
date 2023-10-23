#include <cstdint>

namespace ds {
template <typename _Ty, std::size_t size>
class array {
private:
    _Ty elems[size];
};
} // namespace ds
