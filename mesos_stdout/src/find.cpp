#include "stout/os/find.hpp"
#include <iostream>

int main()
{
  auto files = os::find("/data/liyang/rhel6.2/workspace", "test");
  if (files.isSome())
  {
    for (const auto& x : files.get())
      std::cout << x << std::endl;
  }
  return 0;
}
