#include <cstdio>
#include <iostream>
struct None
{
};

int main()
{
  None none;
  std::cout << sizeof(none) << std::endl;
  std::cout << sizeof(None) << std::endl;
  return 0;
}

