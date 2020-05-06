#include <cstdlib>
#include <iostream>
#include <vector>
#include "heap.h"

int main()
{
    std::vector<int> nums(10, 0);
    for (int i=0; i<10; i++)
        nums[i] = rand() % 100;

    // heap basic operation
    Heap<int>* heap = Heap<int>::create_heap(nums, MIN_HEAP);
    for (int i=0; i<10; ++i)
    {
        int tmp = heap->top();
        std::cout << tmp << std::endl;
        heap->pop();
    }
    return 0;
}
