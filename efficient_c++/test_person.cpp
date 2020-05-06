#include <functional>
#include "benchmark.h"
#include "person_v2.h"
#include "person_v3.h"

void test_person_v2()
{
  ::PersonV2 person("helloworld");
}

void test_person_v3()
{
  ::PersonV3 person("helloworld");
}

int main()
{
  ::Benchmark(std::bind(test_person_v2), "test_person_v2");
  ::Benchmark(std::bind(test_person_v3), "test_person_v3");
}

