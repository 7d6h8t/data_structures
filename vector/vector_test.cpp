#include "vector.h"
#include <iostream>
#include <vector>

int main() {
  std::vector<int32_t> vector_test{1, 2, 3, 4, 5};

  for (const auto& elem : vector_test)
    std::cout << elem << " " << std::flush;
  std::cout << std::endl;

  ds::vector<int32_t> ds_vector1{1, 2, 3, 4, 5};

  std::cout << ds_vector1[2] << std::flush;

  ds_vector1.push_back(6);
  ds_vector1.push_back(7);
  ds_vector1.push_back(8);

  std::cout << ds_vector1[6] << std::flush;

  return 0;
}