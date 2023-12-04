#include "stack.h"
#include <iostream>
#include <stack>

int main() {
  std::stack<int32_t> std_stack;
  std_stack.push(0);
  std_stack.push(1);
  std_stack.push(2);
  std_stack.push(3);
  std_stack.push(4);

  while (!std_stack.empty()) {
    std::cout << std_stack.top() << " " << std::flush;
    std_stack.pop();
  }
  std::cout << std::endl;

  ds::stack<int32_t> ds_stack;
  ds_stack.push(1);
  ds_stack.push(2);
  ds_stack.push(3);
  ds_stack.push(4);
  ds_stack.push(5);

  while (!ds_stack.empty()) {
    std::cout << ds_stack.top() << " " << std::flush;
    ds_stack.pop();
  }
  std::cout << std::endl;

  return 0;
}