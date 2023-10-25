#include <concepts>
#include <cstdint>
#include <stdexcept>

namespace ds {
    template <typename T, std::size_t size>
    class array final {
    private:
        using size_type = std::size_t;

    public:
        template <typename... types>
        requires(std::same_as<T, types> && ...)
        array(const types&... args) {
            size_type index = 0;
            ((elems[index++] = args), ...);
        }

    public:
        T& at(const size_type index) {
            if (index > size)
                throw std::out_of_range("");
            return elems[index];
        }

        const T& at(const size_type index) const {
            if (index > size)
                throw std::out_of_range("");
            return elems[index];
        }

        T& operator[](const size_type index) noexcept {
            return elems[index];
        }

        const T& operator[](const size_type index) const noexcept {
            return elems[index];
        }

    private:
        T elems[size];
    };
} // namespace ds
