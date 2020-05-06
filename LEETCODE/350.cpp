#include <algorithm>
#include <vector>
#include <unordered_map>
#include <iostream>
#include "util.h"
using std::vector;
using std::min;
using std::unordered_map;

vector<int> intersection(vector<int>& nums1, vector<int>& nums2)
{
  if (nums1.empty() || nums2.empty())
    return vector<int>();

  unordered_map<int, int> count1;
  unordered_map<int, int> count2;
  for (auto x : nums1)
    count1[x]++;
  for (auto x : nums2)
    count2[x]++;

  vector<int> ret;
  ret.reserve(nums1.size() < nums2.size() ? nums1.size() : nums2.size());
  for (auto& kv : count1)
  {
    auto mit = count2.find(kv.first);
    if (mit == count2.end())
      continue;
    int count = min(kv.second, mit->second);
    for (int i=0; i<count; ++i)
      ret.push_back(kv.first);
  }
  return ret;
}

int main()
{
  vector<int> nums1 = {1, 2,  1};
  vector<int> nums2 = {2, 2};
  std::cout << ::stringify(intersection(nums1, nums2)) << std::endl;
  return 0;
}
