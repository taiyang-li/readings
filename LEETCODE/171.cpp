#include <vector>
#include <iostream>
#include <string>
#include <cassert>
using std::string;
using std::vector;

int titleToNumber(string s) 
{
  int ret = 0;
  for (size_t i=0; i<s.size(); ++i)
    ret = 26*ret + (s[i] - 'A' + 1);
  return ret;
}

int main()
{
  std::cout << titleToNumber("AA") << std::endl;
  std::cout << titleToNumber("A") << std::endl;
  return 0;
}
