#include "stout/multihashmap.hpp"
#include <iostream>
#include <string>

void show_map(multihashmap<int, std::string>& m)
{
  for (auto& kv : m)
    std::cout << kv.first << ":" << kv.second << std::endl;
}

int main()
{
  multihashmap<int, std::string> a = {{1, "one"}, {2, "two"}, {1, "yi"}};
  a.put(3, "san");
  show_map(a);

  auto b = a.keys();
  for (int x : b)
    std::cout << x << std::endl;

  auto c = a.get(1);
  for (std::string& x : c)
    std::cout << x << std::endl;

  a.remove(1, "one");
  show_map(a);
  std::cout << std::endl;

  a.remove(1);
  show_map(a);

  if (a.contains(2))
    std::cout << "a contains 2" << std::endl;

  if (a.contains(2, "two"))
    std::cout << "a contains (2, two)" << std::endl;
  return 0;

}
