#ifndef __EFFECTIVE_CPP_TRACE_V2_H__
#define __EFFECTIVE_CPP_TRACE_V2_H__

#include <string>
#include <iostream>
#include "benchmark.h"
using std::string;

class TraceV2
{
  public:
    TraceV2(const string& name);
    ~TraceV2();
    void debug(const string& msg);

  private:
    string* name_;
    bool active_;
};

inline TraceV2::TraceV2(const string& name) : name_(NULL), active_(false)
{
  if (active_)
  {
    name_ = new string(name);
    std::cout << "enter function " << *name_ << std::endl;
  }
}

inline void TraceV2::debug(const string& msg)
{
  if (active_)
    std::cout << msg << std::endl;
}

inline TraceV2::~TraceV2()
{
  if (active_)
    std::cout << "exit function" << *name_ << std::endl;
}

#endif  /*TRACE_V2_H*/
