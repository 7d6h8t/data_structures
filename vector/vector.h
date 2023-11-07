#include <concepts>

namespace ds {
    template <typename T>
    class vector {

    public:
        template <typename... types>
        requires(std::same_as<T, types> && ...)
        vector(const types... arg) {}

    private:
    };
} // namespace ds