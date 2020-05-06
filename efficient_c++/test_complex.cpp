#include "complex.h"
#include "benchmark.h"

void test_complex()
{
  ::Complex c1(1.0, 1.0);
  ::Complex c2(2.0, 2.0);
  for (size_t i=0; i<1000000; ++i)
  {
    Complex c3 = c1 + c2;
  }
}

void test_complex1()
{
  ::Complex c1(1.0, 1.0);
  ::Complex c2(2.0, 2.0);
  for (size_t i=0; i<1000000; ++i)
  {
    Complex c3(c1, c2);
  }
}

int main()
{
  ::Benchmark(std::bind(test_complex), "test_complex", 1);
  ::Benchmark(std::bind(test_complex1), "test_complex1", 1);
  return 0;
}
