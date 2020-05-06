#include <cstdlib>
#include "heap.h"

int main()
{
  vector<int> nums(10, 0);
  for (int i=0; i<10; i++)
    nums[i] = rand() % 100;

  // heap basic operation
  Heap* heap = Heap::create_heap(nums);
  for (int i=0; i<10; ++i)
  {
    heap->push(rand()%100);
    heap->show();
    
    int tmp = heap->pop();
    heap->show();
  }
  delete heap;
  return 0;
}
