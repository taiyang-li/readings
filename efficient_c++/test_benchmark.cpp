#include <vector>
#include <functional>
#include "benchmark.h"
using std::vector;

void func1()
{
  vector<int> vec;
  vec.push_back(1);
}

void func2(int i)
{
  vector<int> vec;
  vec.push_back(i);
}

int main()
{
  Benchmark(&func1, "func1");
  Benchmark(std::bind(func2, 1000), "func2");
  return 0;
}
