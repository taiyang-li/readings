#include <string>
#include <cstring>
#include <algorithm>
#include <iostream>
using std::string;
using std::reverse;
using std::min;

string reverseStr(string s, int k)
{
  int len = s.size();
  if ( k > len || k <= 1)
    return s;

  bool revert = true;
  auto prev = s.begin();
  auto curr = s.begin() + k;
  int left = len;
  while (left > 0)
  {
    if (revert)
      reverse(prev, curr);
    revert = ! revert;
    left -= (curr-prev);
    prev = curr;
    curr += min(left, k);
    // std::cout << "left: " << left << std::endl;
  }
  return s;
}

int main()
{
  string str = "abcdefg";
  int k = 2;
  std::cout << reverseStr(str, k) << std::endl;
  return 0;
}
