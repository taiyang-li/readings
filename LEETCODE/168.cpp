#include <vector>
#include <iostream>
#include <string>
#include <map>
#include <cassert>
using std::string;
using std::vector;
using std::map;

string convertToTitle(int n) 
{
  assert(n >= 1);

  string ret = "";
  char tmp;
  while (n)
  {
    tmp = (n-1) % 26 + 'A';
    ret = tmp + ret;
    n = (n-1)/26;
  }
  return ret;
}

int main()
{
  std::cout << convertToTitle(26) << std::endl;
  std::cout << convertToTitle(27) << std::endl;
  std::cout << convertToTitle(28) << std::endl;
  return 0;
}
