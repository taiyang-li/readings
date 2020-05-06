#include <vector>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <cassert>
using std::vector;
using std::string;
using std::istringstream;

int ver2vec(const string& version, vector<int>& nums)
{
  string tmpstr  = version;
  std::replace(tmpstr.begin(), tmpstr.end(), '.', ' ');
  istringstream iss(tmpstr);
  int tmp;
  nums.clear();
  while (iss >> tmp)
    nums.push_back(tmp);
  // find last subversion not 0
  int i = nums.size() - 1;
  for (; i >= 0 && nums[i] == 0; --i);
  return i;
}

int compareVec(vector<int>& left, int m, vector<int>& right, int n)
{
  int i = 0;
  for (i=0; i<=m && i<=n; ++i)
  {
    if (left[i] == right[i])
      continue;
    return (left[i] > right[i] ? 1 : -1);
  }
  return m > n ? 1 : (m == n ? 0 : -1);
}

int compareVersion(string version1, string version2) 
{
  vector<int> nums1;
  vector<int> nums2;
  int m = ver2vec(version1, nums1);
  int n = ver2vec(version2, nums2);
  return compareVec(nums1, m, nums2, n);
}

int main()
{
  std::cout << compareVersion("0.1", "1.1") << std::endl;
  std::cout << compareVersion("1.1", "1.2") << std::endl;
  std::cout << compareVersion("1.2", "13.37") << std::endl;
  std::cout << compareVersion("01", "1") << std::endl;
  return 0;
}

