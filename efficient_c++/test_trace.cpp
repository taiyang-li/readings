#include <functional>
#include "trace_v0.h"
#include "trace_v1.h"
#include "trace_v2.h"
#include "benchmark.h"

int add_one(int x)
{
  return x+1;
}

int add_one_v0(int x)
{
  string name = "add_one_v0";
  ::TraceV0 t(name);
  return x+1;
}

int add_one_v1(int x)
{
  string name = "add_one_v1";
  ::TraceV1 t(name.c_str());
  return x+1;
}

int add_one_v2(int x)
{
  string name = "add_one_v2";
  ::TraceV2 t(name);
  return x+1;
}

int main()
{
  ::Benchmark(std::bind(add_one, 100), "add_one");
  ::Benchmark(std::bind(add_one_v0, 100), "add_one_v0");
  ::Benchmark(std::bind(add_one_v1, 100), "add_one_v1");
  ::Benchmark(std::bind(add_one_v2, 100), "add_one_v2");
  return 0;
}

