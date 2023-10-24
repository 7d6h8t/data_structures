#include <concepts>
#include <cstdint>
namespace ds {
template <typename T, std::size_t size>
class array {
private:
    void initialize() {}

    template <typename... types>
    void initialize(const T& arg, const types&... args) {
        elems[size - sizeof...(args) - 1] = arg;
        initialize(args...);
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
