#include <iostream>
#include <vector>
using std::vector;

int bsearch_pivot(vector<int>& nums, int left, int right)
{
  if (left >= right)
    return -1;

  int mid = left + (right-left)/2;
  if (nums[mid+1] < nums[mid])
    return mid+1;
  if (mid-1 >= left && nums[mid-1] > nums[mid])
    return mid;

  int lret = bsearch_pivot(nums, left, mid-1);
  if (lret != -1)
    return lret;
  int rret = bsearch_pivot(nums, mid+1, right);
  if (rret != -1)
    return rret;
  return -1;
}

int findMin(vector<int>& nums)
{
  if (nums.empty() )
    return 0;

  int idx = bsearch_pivot(nums, 0, nums.size()-1);
  return idx > 0 ? nums[idx] : nums[0];
}

int main()
{
  vector<int> nums;
  int tmp;
  while (std::cin >> tmp)
    nums.push_back(tmp);

  std::cout << "min value: " << findMin(nums);
  return 0;
}
