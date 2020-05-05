#include "stout/hashmap.hpp"
#include <string>
#include <iostream>

int main()
{
  hashmap<int, std::string> a = {{1, "one"}, {2, "two"}, {3, "three"}};

  if (a.contains(1))
    std::cout << "a contains 1" << std::endl;

  if (a.containsValue("one"))
    std::cout << "a containsValue one" << std::endl;

  auto b =  a.get(2);
  if (b.isSome())
    std::cout << "from a get " << b.get() << std::endl;

  auto c = a.keys();
  for (const int& x : c)
    std::cout << x << std::endl;
  
  auto d = a.values();
  for (const std::string& x : d)
    std::cout << x << std::endl;
  return 0;
}
