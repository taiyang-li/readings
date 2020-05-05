#include "stout/cache.hpp"
#include <iostream>
#include <string>

int main()
{
  Cache<int, std::string> a(3);
  a.put(1, "one");
  a.put(2, "two");
  a.put(3, "three");
  std::cout << a << std::endl;

  a.get(2);
  std::cout << a << std::endl;

  a.put(4, "four");
  std::cout << a << std::endl;
  return 0;
}
