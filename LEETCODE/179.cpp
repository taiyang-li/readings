#include <iostream>
#include <string>
#include <cassert>
#include <vector>
#include <algorithm>
#include "util.h"
using std::string;
using std::vector;

string int2str(int n)
{
  char buf[64];
  sprintf(buf, "%d", n);
  return buf;
}

void remove_head_zero(string& str)
{
  int i = 0;
  while (str[i] == '0' && i<int(str.size()-1)) i++;
  if (i > 0)
    str.erase(0, i);
}

bool mycompare(const string& left, const string& right)
{
  // std::cout << "left:" << left << ",right:" << right << std::endl;
  int llen = left.size();
  int rlen = right.size();
  assert(llen != 0 && rlen != 0);

  int len = std::min(llen, rlen);
  int i = 0;
  for (; i<len; i++)
  {
    if (left[i] == right[i])
      continue;
    return left[i] < right[i];
  }

  if (llen == len && rlen == len)
    return true; /* must return false, otherwise program would core(segment fault)*/
  else if (llen != len)
    return mycompare(left.substr(len, llen), right);
  else 
    return mycompare(left, right.substr(len, rlen));
}

string largestNumber(vector<int>& nums)
{
  if (nums.empty())
    return "";

  vector<string> strs;
  for (auto it=nums.begin(); it!=nums.end(); ++it)
    strs.push_back(int2str(*it));
  // std::cout << stringify(strs) << std::endl;

  std::sort(strs.begin(), strs.end(), mycompare);

  string ret;
  for (auto it=strs.rbegin(); it!=strs.rend(); ++it)
    ret.append(*it);
  remove_head_zero(ret);
  return ret;
}

int main()
{
  // vector<int> nums = {3, 30, 34, 5, 9};
  // vector<int> nums = {121,12};
  vector<int> nums = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
  std::cout << largestNumber(nums) << std::endl;
  /*
  if (mycompare("0", "0") )
    std::cout << "true" << std::endl;
  else 
    std::cout << "false" << std::endl;
    */
  return 0;
}
