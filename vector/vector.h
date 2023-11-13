#include <concepts>

namespace ds {
    template <typename T>
    class vector {
    public:
        using value_type = T;
        using size_type = std::size_t;
        using pointer = T*;
        using reference = T&;
        using const_reference = const T&;

    public:
        template <typename... types>
        requires(std::same_as<T, types> && ...)
        vector(const types&... args) {
            size_ = sizeof...(args);
            capaticy_ = size_;
            value_ = new T[size_];
        }

        ~vector() {
            size_ = 0;
            capaticy_ = 0;
            if (value_ != nullptr) {
                delete[] value_;
                value_ = nullptr;
            }
        }

    public:
        reference at(const size_type pos) {
            return *(value_ + pos);
        }

        const_reference at(const size_type pos) const {
            return *(value_ + pos);
        }

        // capacity
        void reserve(const size_type new_cap) {
            capaticy_ = new_cap;
        }

        size_type capacity() const {
            return capaticy_;
        }

    private:
        size_type size_;
        size_type capaticy_;
        value_type* value_;
    };
} // namespace ds