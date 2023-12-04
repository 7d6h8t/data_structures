#include "queue.h"
#include <iostream>
#include <queue>

int main() {
  std::queue<int32_t> std_queue;
  std_queue.push(0);
  std_queue.push(1);
  std_queue.push(2);
  std_queue.push(3);
  std_queue.push(4);

  while (!std_queue.empty()) {
    std::cout << std_queue.front() << " " << std::flush;
    std_queue.pop();
  }
  std::cout << std::endl;

  ds::queue<int32_t> ds_queue;
  ds_queue.push(0);
  ds_queue.push(1);
  ds_queue.push(2);
  ds_queue.push(3);
  ds_queue.push(4);

  while (!ds_queue.empty()) {
    std::cout << ds_queue.front() << " " << std::flush;
    ds_queue.pop();
  }
  std::cout << std::endl;

  return 0;
}