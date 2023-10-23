#include "array.h"
#include <iostream>

template <typename _Ty>
void print(const _Ty arg) {
    std::cout << arg << std::endl;
}

template <typename _Ty, typename... types>
void print(const _Ty arg, types... args) {
    std::cout << arg << ", " << std::flush;
    print(args...);
}

int main() {
    print("hello world", 13, 12.5);
    return 0;
}