#include "list.h"
#include <iostream>
#include <list>

int main() {
    std::list<int32_t> list_test{1, 2, 3, 4};
    ds::list<int32_t> ds_list1{1, 2, 3, 4};

    std::cout << ds_list1.front() << std::endl;
    std::cout << ds_list1.back() << std::endl;

    for (const auto& elem : list_test)
        std::cout << elem << std::flush;
    std::cout << std::endl;
}