#include <algorithm>
#include <string>
#include <cctype>
#include <iostream>
#include "util.h"
using std::string;
using std::find_if;


bool detectCapitalUse(string word)
{
  if (word.empty())
    return false;
  auto it1 = find_if(word.begin(), word.end(), ::islower);
  auto it2 = find_if(word.begin()+1, word.end(), ::isupper);
  if (it1 == word.end() || it2 == word.end())
    return true;
  return false;
}

int main()
{
  std::cout << ::stringify(detectCapitalUse("USA")) << std::endl;
  std::cout << ::stringify(detectCapitalUse("hello")) << std::endl;
  std::cout << ::stringify(detectCapitalUse("Hello")) << std::endl;
  std::cout << ::stringify(detectCapitalUse("HelLo")) << std::endl;
  return 0;
}

