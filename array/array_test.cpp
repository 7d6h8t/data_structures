#include "array.h"
#include <array>
#include <concepts>
#include <iostream>

template <typename T>
concept printable = requires(T arg) { std::cout << arg; };

void print(printable auto const&... args) {
    ((std::cout << args << " " << std::flush), ...) << std::endl;
}

int main() {
    std::array<int32_t, 5> std_array_1;
    std::array<int32_t, 5> std_array_2{1, 2, 3, 4, 5};

    ds::array<int32_t, 5> ds_array_1;
    ds::array<int32_t, 5> ds_array_2{10, 20, 30, 40, 50};

    print(1, 2, 3, "helo", ds_array_2[3]);

    return 0;
}