#include <compare>
#include <concepts>
#include <cstdint>
#include <stdexcept>

namespace ds {
    template <typename T, std::size_t size_>
    class array final {
    private:
        using value_type = T;
        using size_type = std::size_t;
        using reference = value_type&;
        using const_reference = const value_type&;
        using pointer = value_type*;
        using const_pointer = const value_type*;
        using iterator = value_type*;
        using const_iterator = const value_type*;

    public:
        template <typename... types>
        requires(std::same_as<T, types> && ...)
        array(const types&... args) {
            size_type index = 0;
            ((elems_[index++] = args), ...);
        }

    public:
        // element access
        reference at(const size_type index) {
            if (index > size_)
                throw std::out_of_range("");
            return elems_[index];
        }

        const_reference at(const size_type index) const {
            if (index > size_)
                throw std::out_of_range("");
            return elems_[index];
        }

        reference operator[](const size_type index) noexcept {
            return elems_[index];
        }

        const_reference operator[](const size_type index) const noexcept {
            return elems_[index];
        }

        reference front() noexcept {
            return elems_[0];
        }

        const_reference front() const noexcept {
            return elems_[0];
        }

        reference back() noexcept {
            return elems_[size_ - 1];
        }

        const_reference back() const noexcept {
            return elems_[size_ - 1];
        }

        pointer data() noexcept {
            return static_cast<pointer>(elems_);
        }

        const_pointer data() const noexcept {
            return static_cast<const_pointer>(elems_);
        }
        // iterators
        iterator begin() noexcept {
            return static_cast<iterator>(data());
        }

        const_iterator begin() const noexcept {
            return static_cast<const_iterator>(data());
        }

        const_iterator cbegin() const noexcept {
            return static_cast<const_iterator>(data());
        }

        iterator end() noexcept {
            return static_cast<iterator>(data() + size_);
        }

        const_iterator end() const noexcept {
            return static_cast<const_iterator>(data() + size_);
        }

        const_iterator cend() const noexcept {
            return static_cast<const_iterator>(data() + size_);
        }
        // capacity
        size_type size() const noexcept {
            return size_;
        }

        size_type max_size() const noexcept {
            return size_;
        }

        bool empty() const noexcept {
            return size() == 0;
        }

    private:
        T elems_[size_];
    };

    template <typename T, std::size_t size>
    std::strong_ordering operator<=>(const ds::array<T, size>& lhs,
                                     const ds::array<T, size>& rhs) noexcept {
        if (lhs.size() < rhs.size())
            return std::strong_ordering::less;

        if (lhs.size() > rhs.size())
            return std::strong_ordering::greater;

        for (std::size_t i = 0; i < lhs.size(); ++i) {
            if (lhs[i] < rhs[i])
                return std::strong_ordering::less;

            if (lhs[i] > rhs[i])
                return std::strong_ordering::greater;
        }

        return std::strong_ordering::equal;
    }

    template <typename T, std::size_t size>
    bool operator==(const ds::array<T, size>& lhs,
                    const ds::array<T, size>& rhs) noexcept {
        return (lhs <=> rhs) == std::strong_ordering::equal;
    }
} // namespace ds
