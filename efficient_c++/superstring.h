#ifndef __EFFECTIVE_CPP_SUPERSTRING_H__
#define __EFFECTIVE_CPP_SUPERSTRING_H__

#include <cstring>
#include <iostream>

class SuperString
{
  public:
    SuperString(const char* str = 0);
    SuperString(const SuperString& other);
    ~SuperString();

    SuperString& operator=(const SuperString& other);

    friend std::ostream& operator<<(std::ostream& os, const SuperString& str);

  private:
      char* str_;
};

#endif  /*SUPERSTRING_H*/
