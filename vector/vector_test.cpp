#include "vector.h"
#include <iostream>
#include <vector>

int main() {
    std::vector<int32_t> vector_test{1, 2, 3, 4, 5};

    for (const auto& elem : vector_test)
        std::cout << elem << " " << std::flush;
    std::cout << std::endl;

    ds::vector<int32_t> ds_vector1{1, 2, 3, 4, 5};

    return 0;
}