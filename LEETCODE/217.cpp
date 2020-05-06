#include <set>
#include <vector>
using std::vector;
using std::set;

bool containsDuplicate(vector<int>& nums)
{
  set<int> s(nums.begin(), nums.end());
  return s.size() != nums.size();
}
