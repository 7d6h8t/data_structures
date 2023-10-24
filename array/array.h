#include <concepts>
#include <cstdint>
namespace ds {
template <typename T, std::size_t size>
class array {
public:
    template <typename... types>
    array(const types&... args) {
        std::size_t index = 0;
        ((elems[index++] = args), ...);
    }

private:
    T elems[size];
};
} // namespace ds
