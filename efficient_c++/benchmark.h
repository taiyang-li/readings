#ifndef __EFFECTIVE_CPP_BENCHMARK_H__
#define __EFFECTIVE_CPP_BENCHMARK_H__

#include <cstdio>
#include <string>
#include <iostream>
#include <functional>
#include "stopwatch.hpp"
using std::string;

typedef std::function<void ()> Func;

class Benchmark
{
  public:
    Benchmark(const Func& func, const string& name, size_t times=1000000);
    ~Benchmark();

  private:
    Func func_;
    string name_;
    size_t times_;
};

Benchmark::Benchmark(const Func& func, const string& name, size_t times) : func_(func), name_(name), times_(times) {}

Benchmark::~Benchmark()
{
  ::Stopwatch sw;
  sw.start();
  for (size_t i=0; i<times_; ++i)
    func_();
  sw.stop();
  std::cout << "name:" << name_ << ",time(s):" << sw.elapsed() << "/" << times_ << std::endl;
}
#endif  /*BENCHMARK_H*/
