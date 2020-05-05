#include "stout/os/getcwd.hpp"
#include <iostream>

int main()
{
  std::cout << os::getcwd() << std::endl;
  return 0;
}
