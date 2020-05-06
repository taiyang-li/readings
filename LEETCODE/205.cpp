#include <vector>
#include <iostream>
#include <string>
#include "util.h"
using std::vector;
using std::string;

void isomorphic_unify(string& str)
{
  if (str.empty())
    return;

  // std::cout << "previous:" << str << std::endl;
  char chmap[256] = {0};
  char ch = 'a';
  for (auto it=str.begin(); it!=str.end(); ++it)
  {
    if (chmap[(size_t)*it])
    {
      *it = chmap[(size_t)*it];
      continue;
    }
    chmap[(size_t)*it] = ch;
    *it = ch++;
  }
  // std::cout << "current:" << str << std::endl; 
}

bool isIsomorphic(string s, string t)
{
  isomorphic_unify(s);
  isomorphic_unify(t);
  return s == t;
}

int main()
{
  std::cout << stringify(isIsomorphic("egg", "add")) << std::endl;
  std::cout << stringify(isIsomorphic("for", "bar")) << std::endl;
  std::cout << stringify(isIsomorphic("paper", "title")) << std::endl;
  return 0;
}

