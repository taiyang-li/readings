#include <iostream>
#include <cstdint>
#include <algorithm>
#include <vector>
#include "util.h"
using std::vector;
using std::swap;
using std::max;

int doRob(vector<int>& nums, int idx)
{
  if (idx >= nums.size())
    return 0;

  int candidate1 = nums[idx] + doRob(nums, idx+2);
  int candidate2 = nums[idx+1] + doRob(nums, idx+3);
  return candidate1 > candidate2 ? candidate1 : candidate2;
}

int rob(vector<int>& nums)
{
  if (nums.empty())
    return 0;
  return doRob(nums, 0); 
}

int rob1(vector<int>& nums)
{
  int len = nums.size();
  if (len == 0)
    return 0;
  if (len == 1)
    return nums[0];
  if (len == 2)
    return max(nums[0], nums[1]);

  int* dp = new int[nums.size()];
  dp[0] = nums[0];
  dp[1] = max(nums[0], nums[1]);
  for (int i=2; i<len; ++i)
    dp[i] = max(dp[i-1], nums[i]+dp[i-2]);
  delete [] dp;
  return dp[len-1];
}

int main()
{
  vector<int> nums = {183,219,57,193,94,233,202,154,65,240,97,234,100,249,186,66,90,238,168,128,177,235,50,81,185,165,217,207,88,80,112,78,135,62,228,247,211};
  std::cout << rob(nums) << std::endl;
  return 0;
}

