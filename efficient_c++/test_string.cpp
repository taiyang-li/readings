#include "benchmark.h"
#include <string>
using std::string;

void test_string1()
{
  string s1 = "hello";
  string s2 = "world";
  string s3;
  s3 = s1 + s2;
}

void test_string2()
{
  string s1 = "hello";
  string s2 = "world";
  string s3 = s1 + s2;
}

void test_string3()
{
  string s1 = "hello";
  string s2 = "world";
  string s3 = s1;
  s3 += s2;
}

int main()
{
  ::Benchmark(std::bind(test_string1), "test_string1");
  ::Benchmark(std::bind(test_string2), "test_string2");
  ::Benchmark(std::bind(test_string3), "test_string3");
  return 0;
}
