#include <vector>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include "util.h"
#include "heap.h"
using std::vector;
using std::sort;

int main()
{
  vector<int> nums(10000, 0);
  for (int i=0; i<10000; ++i)
    nums[i] = rand() % 100;

  vector<int> head(nums.begin(), nums.begin()+10);
  Heap* heap = Heap::create_heap(head);
  int idx = 10;
  while (idx < 10000)
  {
    std::cout << "push: " << nums[idx] << std::endl;
    heap->push(nums[idx]);
    heap->show();

    std::cout << "pop: " << std::endl;
    heap->pop();
    heap->show();
    idx++;
  }
  heap->show();

  sort(nums.begin(), nums.end());
  std::cout << "expect: ";
  for (auto it=nums.begin(); it!=nums.begin()+10; ++it)
    std::cout << *it << " ";
  std::cout << std::endl;
  return 0;
}
