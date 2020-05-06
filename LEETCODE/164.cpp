#include <vector>
#include <iostream>
#include <cstring>
using std::vector;

char bitmap[268435456L];

#define SET_BITMAP(n) (bitmap[(n)/8] |= (1<<(7-(n)%8)))
#define CLR_BITMAP(n) (bitmap[(n)/8] &= (~(1<<(7-(n)%8))))
#define GET_BITMAP(n) (bitmap[(n)/8] & (1<<(7-(n)%8)))

int maximumGap(vector<int>& nums) 
{
  if (nums.size() <= 1)
    return 0;

  int max_v = nums[0];
  int min_v = nums[0];
  memset(bitmap, 0, sizeof(bitmap));
  for (auto it=nums.begin(); it!=nums.end(); ++it)
  {
    SET_BITMAP(*it);
    if (*it > max_v)
      max_v = *it;
    if (*it < min_v)
      min_v = *it;
  }

  int max_diff = 0;
  int last = -1;
  for (size_t i=min_v; i<=max_v; i++)
  {
    if (GET_BITMAP(i))
    {
      if (last == -1)
      {
        last = i;
        continue;
      }
      if (i - last > max_diff)
        max_diff = i - last;
      last = i;
    }
  }
  return max_diff;
}

int main() 
{
  vector<int> nums = {1,2,3,4,5,6,7,3330353};
  std::cout << maximumGap(nums) << std::endl;
  return 0;
}


