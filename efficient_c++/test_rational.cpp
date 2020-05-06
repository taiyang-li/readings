#include "rational.h"
#include "benchmark.h"

void test_rational1()
{
  // std::cout << "1 start" << std::endl;; 
  Rational r(100);
  // std::cout << "1 end" << std::endl;; 
}

void test_rational2()
{
  // std::cout << "2 start" << std::endl;; 
  Rational r = Rational(100);
  // std::cout << "1 end" << std::endl;; 
}

void test_rational3()
{
  // std::cout << "3 start" << std::endl;
  Rational r = 100;
  // std::cout << "3 end" << std::endl;
}

int main ()
{
  /*
  test_rational1();
  test_rational2();
  test_rational3();
  */
  ::Benchmark(std::bind(test_rational1), "test_rational1");
  ::Benchmark(std::bind(test_rational2), "test_rational2");
  ::Benchmark(std::bind(test_rational3), "test_rational3");
  return 0;
}

