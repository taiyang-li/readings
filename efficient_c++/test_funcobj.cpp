#include <algorithm>
#include <numeric>
#include "benchmark.h"

int mult(int x, int y) {return x*y;}

class Mult
{
  public:
    int operator()(int x, int y) const
    {
      return x*y;
    }
};

void test_func(int* a, int size)
{
  int tmp = std::accumulate(&a[0], &a[size], 1, mult);
  (void)tmp;
}

void test_funcobj(int* a, int size)
{
  int tmp = std::accumulate(&a[0], &a[size], 1, Mult());
  (void)tmp;
}

int main()
{
  int a[10] = {1, 2, 3, 5, 7, 11, 13, 17, 19, 23};
  ::Benchmark(std::bind(test_func, a, 10), "test_func");
  ::Benchmark(std::bind(test_funcobj, a, 10), "test_funcobj");
  return 0;
}

