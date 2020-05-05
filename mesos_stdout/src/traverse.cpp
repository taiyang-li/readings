#include <map>
#include <string>
#include <iostream>
#include <vector>

int main()
{
  std::vector<int> a = {1, 2, 3};
  std::map<int, std::string> b = {{1, "one"}, {2, "two"}, {3, "three"}};
  
  for(auto& elem : a)
    std::cout << elem << std::endl;

  for (auto& kv : b)
    std::cout << kv.first << " : " << kv.second << std::endl;

  return 0;
}
