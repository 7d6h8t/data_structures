#include <concepts>
#include <cstdint>
#include <stdexcept>

namespace ds {
    template <typename T, std::size_t size>
    class array final {
    private:
        using value_type = T;
        using size_type = std::size_t;
        using reference = value_type&;
        using const_reference = const value_type&;
        using pointer = value_type*;
        using const_pointer = const value_type*;

    public:
        template <typename... types>
        requires(std::same_as<T, types> && ...)
        array(const types&... args) {
            size_type index = 0;
            ((elems[index++] = args), ...);
        }

    public:
        reference at(const size_type index) {
            if (index > size)
                throw std::out_of_range("");
            return elems[index];
        }

        const_reference at(const size_type index) const {
            if (index > size)
                throw std::out_of_range("");
            return elems[index];
        }

        reference operator[](const size_type index) noexcept {
            return elems[index];
        }

        const_reference operator[](const size_type index) const noexcept {
            return elems[index];
        }

        reference front() noexcept {
            return elems[0];
        }

        const_reference front() const noexcept {
            return elems[0];
        }

        reference back() noexcept {
            return elems[size - 1];
        }

        const_reference back() const noexcept {
            return elems[size - 1];
        }

        pointer data() noexcept {
            return elems;
        }

        const_pointer data() const noexcept {
            return elems;
        }

    private:
        T elems[size];
    };
} // namespace ds
