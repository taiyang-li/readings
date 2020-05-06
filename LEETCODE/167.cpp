#include <vector>
#include <iostream>
#include <string>
#include <map>
using std::string;
using std::vector;
using std::map;

vector<int> twoSum(vector<int>& numbers, int target)
{
  vector<int> ret(2, -1);
  map<int, int> idx_by_val;
  for (auto it=numbers.begin(); it!=numbers.end(); ++it)
  {
    if (idx_by_val.count(*it) > 0)
    {
      ret[0] = idx_by_val[*it];
      ret[1] = (it - numbers.begin()) + 1;
      break;
    }
    idx_by_val[target-(*it)] = (it-numbers.begin()) + 1;
  }
  return ret;
}

int main()
{
  vector<int> nums = {2, 7, 11, 15};
  int target = 9;
  vector<int> ret = twoSum(nums, target);
  std::cout << ret[0] << ":" << ret[1] << std::endl;
  return 0;
}
