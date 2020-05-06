#ifndef __EFFECTIVE_CPP_TRACE_V1_H__
#define __EFFECTIVE_CPP_TRACE_V1_H__

#include <string>
#include <iostream>
#include "benchmark.h"
using std::string;

class TraceV1
{
  public:
    TraceV1(const char* name);
    ~TraceV1();
    void debug(const char* msg);

  private:
    const char* name_;
    bool active_;
};

inline TraceV1::TraceV1(const char* name) : name_(name), active_(false)
{
  if (active_)
    std::cout << "enter function " << name_ << std::endl;
}

inline void TraceV1::debug(const char* msg)
{
  if (active_)
    std::cout << msg << std::endl;
}

inline TraceV1::~TraceV1()
{
  if (active_)
    std::cout << "exit function" << name_ << std::endl;
}

#endif  /*TRACE_V0_H*/
