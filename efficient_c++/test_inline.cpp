#include "benchmark.h"
#include "stopwatch.hpp"
#include "calc.h"

void test_inlined()
{
  int tmp;
  for (int i=0; i<10000000; ++i)
    tmp = ::inlined_add(i, i);
}

void test_uninlined()
{
  int tmp;
  for (int i=0; i<10000000; ++i)
    tmp = ::uninlined_add(i, i);
}

int main()
{
  /*
  ::Benchmark(std::bind(test_inlined), "test_inlined", 1);
  ::Benchmark(std::bind(test_uninlined), "test_uninlined", 1);
  */

  Stopwatch sw;

  sw.start();
  test_inlined();
  sw.stop();
  std::cout << sw.elapsed() << std::endl;

  sw.start();
  test_uninlined();
  sw.stop();
  std::cout << sw.elapsed() << std::endl;

  return 0;
}
