// given a target value, and a vector, erase all values which equal to target value
#include <vector>
#include <iostream>
#include "util.h"
using std::vector;

void my_erase(vector<int>& nums, int target)
{
  if (nums.empty()) return;

  int beg = 0;
  int len = 0;
  int offset = 0;
  for (size_t i=0; i<nums.size(); ++i)
  {
    if (nums[i] != target)
    {
      len++;
      continue;
    }
    
    if (offset != 0 && len != 0)
      for (size_t j=beg; j<beg+len; ++j)
        nums[j-offset] = nums[j];

    beg = i+1;
    len = 0;
    offset++;
  }
  if (offset != 0 && len != 0)
    for (size_t j=beg; j<beg+len; ++j)
      nums[j-offset] = nums[j];
  for (size_t i=nums.size()-offset; i<nums.size(); ++i)
    nums[i] = target;
}

int main()
{
  vector<int> nums = {1, 2, 3, 3, 2, 5, 2};
  vector<int> nums1 = {3, 3, 3, 2};
  vector<int> nums2 = {2, 2, 3, 2};
  my_erase(nums, 2);
  my_erase(nums1, 2);
  my_erase(nums2, 2);
  std::cout << ::stringify(nums) << std::endl;
  std::cout << ::stringify(nums1) << std::endl;
  std::cout << ::stringify(nums2) << std::endl;
  return 0;
}

