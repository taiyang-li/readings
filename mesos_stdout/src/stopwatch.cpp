#include "stout/stopwatch.hpp"
#include <iostream>

void foo()
{
  for(size_t i=0; i<100000000; i++)
    ;
}

int main()
{
  Stopwatch w;
  w.start();
  foo();
  w.stop();
  std::cout << w.elapsed() << std::endl;
  return 0;
}
