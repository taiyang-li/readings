#include <string>
#include <iostream>
#include <algorithm>
using std::string;
using std::max;

int findLUSlength(string a, string b)
{
  int lena = a.size();
  int lenb = a.size();
  if (lena != lenb)
    return max(lena, lenb);
  return (a == b ) ? -1 : a.size();
}

int main()
{
  std::cout << findLUSlength("abc", "acc");
  return 0;
}
