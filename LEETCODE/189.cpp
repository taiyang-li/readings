#include <iostream>
#include <cstdint>
#include <algorithm>
#include <vector>
#include "util.h"
using std::vector;
using std::swap;

void reverse_partial(vector<int>& nums, int begin, int end)
{
  if (end - begin <= 0)
    return;

  int len = end-begin;
  for (int i=0; i<len/2; ++i)
    swap(nums[begin+i], nums[end-1-i]);
}

void rotate(vector<int>& nums, int k) 
{
  int len = nums.size();
  int new_k = k % len;
  
  reverse_partial(nums, 0, len-new_k);
  reverse_partial(nums, len-new_k, len);
  reverse_partial(nums, 0, len);
}

int main()
{
  vector<int> nums = {1,2,3,4,5,6,7};
  int k = 3;
  rotate(nums, k);
  std::cout << ::stringify(nums) << std::endl;
  return 0;
}

