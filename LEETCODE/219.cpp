#include <set>
#include <vector>
#include <queue>
using std::vector;
using std::set;
using std::queue;

bool containsNearbyDuplicate(vector<int>& nums, int k)
{
  if (nums.empty() || k <= 0)
    return false;

  queue<int> q;
  set<int> s;
  int count = 0;
  for (auto it=nums.begin(); it!=nums.end(); ++it)
  {
    if (s.find(*it) != s.end())
      return true;
    
    if (count == k)
    {
      int oldest = q.front();
      q.pop();
      s.erase(oldest);
      count--;
    }
    q.push(*it);
    s.insert(*it);
    count++;
  }
  return false;
}
