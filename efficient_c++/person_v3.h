#ifndef __EFFECTIVE_CPP_PERSON_V3_H__
#define __EFFECTIVE_CPP_PERSON_V3_H__

#include "superstring.h"

class PersonV3 
{
  public:
    PersonV3(const char* name) : name_(name) {}
    ~PersonV3() {}

  private:
    ::SuperString name_;
};
#endif  
