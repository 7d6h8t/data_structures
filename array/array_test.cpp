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
    ds::array<int32_t, 5> array_1;
    ds::array<int32_t, 5> array_2{10, 20, 30, 40, 50};
    ds::array<int32_t, 5> array_3{10, 20, 30, 40, 51};

    if (array_2 == array_3)
        std::cout << "same array" << std::endl;

    for (const int32_t elem : array_2)
        std::cout << elem << ", " << std::flush;
    std::cout << std::endl;

    array_3[4] = 50;
    print(1, 2, 3, "helo", array_3[3]);

    return 0;
}