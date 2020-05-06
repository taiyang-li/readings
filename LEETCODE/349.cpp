#include <algorithm>
#include <vector>
#include <unordered_set>
#include <iostream>
#include "util.h"
using std::vector;
using std::unordered_set;

vector<int> intersection(vector<int>& nums1, vector<int>& nums2)
{
  if (nums1.empty() || nums2.empty())
    return vector<int>();

  size_t len1 = nums1.size();
  size_t len2 = nums2.size();
  vector<int>* vec_ptr = len1 < len2 ? &nums1 : &nums2;
  unordered_set<int>* set_ptr = len1 < len2 ? (new unordered_set<int>(nums2.begin(), nums2.end())) 
    : (new unordered_set<int>(nums1.begin(), nums1.end()));

  unordered_set<int> tmp;
  for (auto it=vec_ptr->begin(); it!=vec_ptr->end(); ++it)
    if (set_ptr->count(*it))
      tmp.insert(*it);
  delete set_ptr;
  return vector<int>(tmp.begin(), tmp.end());
}

int main()
{
  vector<int> nums1 = {1, 2, 3, 3};
  vector<int> nums2 = {1, 2, 3, 4};
  std::cout << ::stringify(intersection(nums1, nums2)) << std::endl;
  return 0;
}
