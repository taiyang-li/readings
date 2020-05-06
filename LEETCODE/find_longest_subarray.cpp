#include <cstdio>
#include <vector>
#include <iostream>
#include "util.h"
using std::vector;

#define SET_BITMAP(n) (bitmap[(n)/8] |= (1<<(7-(n)%8)))
#define CLR_BITMAP(n) (bitmap[(n)/8] &= (~(1<<(7-(n)%8))))
#define GET_BITMAP(n) (bitmap[(n)/8] & (1<<(7-(n)%8)))

void find_longest_subarray(vector<int>& nums, vector<int>& result)
{
  int len = nums.size();
  if (len == 0)
    return;

  // first step, calculate max and min
  int max = nums[0];
  int min = nums[0];
  for (auto it=nums.begin()+1; it!=nums.end(); ++it)
  {
    if (*it > max) 
      max = *it;
    if (*it < min)
      min = *it;
  }

  // second step, set bits
  char* bitmap = new char[(max-min+8)/8];
  for (auto it=nums.begin(); it!=nums.end(); ++it)
    SET_BITMAP(*it-min);

  // third step, get longest bitarray
  int curr_bit = 0;
  int last_bit = 0;
  int curr_pos = 0;
  int curr_len = 0;
  int max_pos = 0;
  int max_len = 0;
  int i = 0;
  for (; i<(max-min+1); ++i)
  {
    curr_bit = GET_BITMAP(i);
    if (curr_bit)
    {
      curr_len++;
      if (! last_bit)
        curr_pos = i;
    }
    else
    {
      if (curr_len > max_len)
      {
        max_len = curr_len;
        max_pos = curr_pos;
      }
      curr_len = 0;
    }
    last_bit = curr_bit;
  }
  if (last_bit && curr_len > max_len)
  {
    max_len = curr_len;
    max_pos = curr_pos;
  }

  // fouth step, get longest subarray
  for (i=max_pos; i<max_pos+max_len; ++i)
    result.push_back(i+min);

  delete [] bitmap;
}

int main()
{
  vector<int> nums = {-1, 1, 2, 3, 5, 6, 7, 8};
  vector<int> result;
  find_longest_subarray(nums, result);
  std::cout << ::stringify(result) << std::endl;
  return 0;
}

