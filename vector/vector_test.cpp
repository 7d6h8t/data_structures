#include "vector.h"
#include <iostream>
#include <vector>

int main() {
  std::vector<int32_t> vector_test{1, 2, 3, 4, 5};
  vector_test.insert(vector_test.begin(), 10);

  for (const auto& elem : vector_test)
    std::cout << elem << " " << std::flush;
  std::cout << std::endl;

  ds::vector<int32_t> ds_vector1{1, 2, 3, 4, 5};

  ds_vector1.insert(ds_vector1.begin(), 0);

  ds_vector1.push_back(6);
  ds_vector1.push_back(7);
  ds_vector1.push_back(8);

  ds_vector1.insert(ds_vector1.begin() + 2, 11);

  ds_vector1.erase(ds_vector1.begin() + 2);

  ds_vector1.erase(ds_vector1.begin() + 2);

  for (const auto& elem : ds_vector1)
    std::cout << elem << " " << std::flush;
  std::cout << std::endl;

  return 0;
}