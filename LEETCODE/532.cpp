#include <set>
#include <map>
#include <vector>
#include <utility>
#include <iostream>
using std::map;
using std::set;
using std::vector;
using std::make_pair;

int findPairs(vector<int>& nums, int k)
{
  map<int, int> pairs;
  set<int> memos;

  for (auto it=nums.begin(); it!=nums.end(); ++it)
  {
    if (memos.count(*it+k) > 0)
      pairs.insert(make_pair(*it, *it+k));
    if (memos.count(*it-k) > 0)
      pairs.insert(make_pair(*it-k, *it));
    memos.insert(*it);
  }

  return pairs.size();
}

int main()
{
  vector<int> nums1 = {3, 1, 4, 1, 5};
  vector<int> nums2 = {1, 2, 3, 4, 5};
  vector<int> nums3 = {1, 3, 1, 5, 4};

  std::cout << findPairs(nums1, 2) << std::endl;
  std::cout << findPairs(nums2, 1) << std::endl;
  std::cout << findPairs(nums3, 0) << std::endl;
  return 0;
}
