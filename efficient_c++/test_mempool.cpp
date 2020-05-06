#include "rational.h"
#include "rational_v1.h"
#include "rational_v2.h"
#include "rational_v3.h"
#include "rational_v4.h"
#include "benchmark.h"

void test_mempool_v0()
{
  Rational *array[1000];
  for (int i=0; i<100000; ++i)
  {
    for (int j=0; j<1000; ++j)
      array[j] = new Rational(j);
    for (int j=0; j<1000; ++j)
      delete array[j];
  }
}

void test_mempool_v1()
{
  RationalV1::new_mempool();
  RationalV1 *array[1000];
  for (int i=0; i<100000; ++i)
  {
    for (int j=0; j<1000; ++j)
      array[j] = new RationalV1(j);
    for (int j=0; j<1000; ++j)
      delete array[j];
  }
  RationalV1::delete_mempool();
}

void test_mempool_v2()
{
  RationalV2::new_mempool();
  RationalV2 *array[1000];
  for (int i=0; i<100000; ++i)
  {
    for (int j=0; j<1000; ++j)
      array[j] = new RationalV2(j);
    for (int j=0; j<1000; ++j)
      delete array[j];
  }
  RationalV2::delete_mempool();
}

void test_mempool_v3()
{
  RationalV3::new_mempool();
  RationalV3 *array[1000];
  for (int i=0; i<100000; ++i)
  {
    for (int j=0; j<1000; ++j)
      array[j] = new RationalV3(j);
    for (int j=0; j<1000; ++j)
      delete array[j];
  }
  RationalV3::delete_mempool();
}

void test_mempool_v4()
{
  RationalV4::new_mempool();
  RationalV4 *array[1000];
  for (int i=0; i<100000; ++i)
  {
    for (int j=0; j<1000; ++j)
      array[j] = new RationalV4(j);
    for (int j=0; j<1000; ++j)
      delete array[j];
  }
  RationalV4::delete_mempool();
}

int main()
{
  ::Benchmark(std::bind(test_mempool_v0), "test_mempool_v0", 1);
  ::Benchmark(std::bind(test_mempool_v1), "test_mempool_v1", 1);
  ::Benchmark(std::bind(test_mempool_v2), "test_mempool_v2", 1);
  ::Benchmark(std::bind(test_mempool_v3), "test_mempool_v3", 1);
  ::Benchmark(std::bind(test_mempool_v4), "test_mempool_v4", 1);
  return 0;
}
