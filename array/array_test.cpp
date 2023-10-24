#include "array.h"
#include <array>
#include <concepts>
#include <iostream>

template <typename _Ty>
void print(const _Ty& arg) {
    std::cout << arg << std::flush;
}

template <typename _Ty, typename... types>
void print(const _Ty& arg, const types&... args) {
    std::cout << arg << " " << std::flush;
    print(args...);
    std::cout << std::endl;
}

template <typename T>
concept Addable = requires(T a, T b) { a + b; };

template <Addable... types>
void add(const types&... args) {
    std::cout << (... + args) << std::flush;
}

int main() {
    std::array<int32_t, 5> std_array_1;
    std::array<int32_t, 5> std_array_2{1, 2, 3, 4, 5};

    ds::array<int32_t, 5> ds_array_1;
    ds::array<int32_t, 5> ds_array_2{10, 20, 30, 40, 50};

    return 0;
}