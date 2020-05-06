#include <vector>
#include <iostream>
using std::vector;

int max_of_3(int a, int b, int c)
{
  return (a>b) ? ((a>c ? a : c )) : ((b>c ? b: c));
}

int min_of_3(int a, int b, int c)
{
  return (a<b) ? ((a<c? a : c)) : ((b<c ? b : c));
}
int maxProduct(vector<int>& nums)
{
  if (nums.empty())
    return 0;

  int product = nums[0];
  int curr_maxp = nums[0];
  int curr_minp = nums[0];
  int next_maxp = 0;
  int next_minp = 0;
  for (size_t i=1; i<nums.size(); ++i)
  {
    next_maxp = max_of_3(curr_maxp*nums[i], nums[i], curr_minp*nums[i]);
    next_minp = min_of_3(curr_maxp*nums[i], nums[i], curr_minp*nums[i]);
    curr_maxp = next_maxp;
    curr_minp = next_minp;

    if (curr_maxp > product)
      product = curr_maxp;
  }
  return product;
}



