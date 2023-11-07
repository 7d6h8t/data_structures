#include <iostream>
#include <vector>

int main() {
    std::vector<int32_t> vector_test{1, 2, 3, 4, 5};

    for (const auto& elem : vector_test)
        std::cout << elem << " " << std::flush;
    std::cout << std::endl;
    return 0;
}