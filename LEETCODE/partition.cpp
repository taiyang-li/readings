// problem: given an array, its element only have 3 values: 0, 1, 2
// please rearrage this array, such that all 0 on the left side of array, all 1 on the right side and 2 in middle
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <ctime>
#include <vector>
#include "util.h"
using std::swap;
using std::vector;

void rearrange(int* arr, int len)
{
  if (! arr || len == 0)
    return;

  int right = len - 1;
  int left = 0;
  int mid = 0;
  while (mid <= right)
  {
    int val = arr[mid];
    if (val == 0)
    {
      swap(arr[left], arr[mid]);
      left++;
      mid++;
    }
    else if (val == 2)
    {
      mid++;
    }
    else 
    {
      swap(arr[mid], arr[right]);
      right--;
    }
  }
}

int main()
{
  int arr[100] = {0}; 
  for (int i=0; i<100; ++i)
    arr[i] = rand() % 3;
  std::cout << ::stringify(std::vector<int>(arr, arr+100)) << std::endl;
  
  rearrange(arr, 100);
  std::cout << ::stringify(std::vector<int>(arr, arr+100)) << std::endl;
  return 0;
}

