#include <vector>
#include <iostream>
#include <string>
#include <cassert>
#include <cassert>
using std::string;
using std::vector;

int majorityElement(vector<int>& nums)
{
  assert(nums.size() >= 1);
  int count = 1;
  int major = nums[0];
  for (size_t i=1; i<nums.size(); i++)
  {
    if (count == 0)
    {
      count = 1;
      major = nums[i];
    }
    else if (major == nums[i])
    {
      count++;
    }
    else 
    {
      count--;
    }
  }
  return major;
}

int main()
{
  vector<int> nums = {1,2,2,2,3};
  std::cout << majorityElement(nums) << std::endl;
  return 0;
}
