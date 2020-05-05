#include "stout/os/fcntl.hpp"
#include "stout/stringify.hpp"
#include <iostream>
#include <unistd.h>
#include <cstring>

int main()
{
  os::nonblock(0);
  char buf[1024];
  memset(buf, 0, 1024);
  int n = read(0, buf, 1024);
  if (n < 0)
    std::cout << "read failed" << std::endl;
  std::cout << stringify(os::isNonblock(0).get()) << std::endl;
  return 0;
}
