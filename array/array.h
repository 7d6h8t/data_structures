#include <concepts>
#include <cstdint>
namespace ds {
template <typename T, std::size_t size>
class array {
private:
    template <typename... types>
    void initialize(const types&... args) {
        std::size_t index = 0;
        ((elems[index++] = args), ...);
    }

public:
    template <typename... types>
    array(const types&... args) {
        initialize(args...);
    }

private:
    T elems[size];
};
} // namespace ds
