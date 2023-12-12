#include "list.h"
#include <format>
#include <iostream>
#include <iterator>
#include <list>

int main()
{
  std::list<int32_t> list_test{1, 3, 4};
  std::list<int32_t>::iterator itr = list_test.begin();
  list_test.insert(++itr, 2);

  std::cout << "std::list = " << std::flush;
  for (const auto& elem : list_test)
    std::cout << std::format("{} ", elem) << std::flush;
  std::cout << std::endl;

  ds::list<int32_t> ds_list1{1, 2, 3};
  ds::list<int32_t> ds_list2{1, 2, 3, 4};

  std::cout << ds_list1.front() << std::endl;
  std::cout << ds_list1.back() << std::endl;
  ds_list1.push_front(std::move(0));
  ds_list1.push_back(5);
  std::cout << ds_list1.back() << std::endl;
  std::cout << ds_list1.size() << std::endl;

  ds_list1.pop_front();
  std::cout << "ds::list = " << std::flush;
  for (const auto& elem : ds_list1)
    std::cout << std::format("{} ", elem) << std::flush;
  std::cout << std::endl;
}