#ifndef __EFFECTIVE_CPP_PERSON_V2_H__
#define __EFFECTIVE_CPP_PERSON_V2_H__

#include "superstring.h"

class PersonV2 
{
  public:
    PersonV2(const char* name) {name_ = name;}
    ~PersonV2() {}

  private:
    ::SuperString name_;
};
#endif  
