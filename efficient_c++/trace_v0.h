#ifndef __EFFECTIVE_CPP_TRACE_V0_H__
#define __EFFECTIVE_CPP_TRACE_V0_H__

#include <string>
#include <iostream>
#include "benchmark.h"
using std::string;

class TraceV0
{
  public:
    TraceV0(const string& name);
    ~TraceV0();
    void debug(const string& msg);

  private:
    string name_;
    bool active_;
};

inline TraceV0::TraceV0(const string& name) : name_(name), active_(false)
{
  if (active_)
    std::cout << "enter function " << name_ << std::endl;
}

inline void TraceV0::debug(const string& msg)
{
  if (active_)
    std::cout << msg << std::endl;
}

inline TraceV0::~TraceV0()
{
  if (active_)
    std::cout << "exit function" << name_ << std::endl;
}

#endif  /*TRACE_V0_H*/
