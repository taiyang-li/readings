#include "superstring.h"

SuperString::SuperString(const char* str) : str_(NULL)
{
  if (str)
  {
    str_ = new char[strlen(str)+1];
    strcpy(str_, str);
  }
}

SuperString::~SuperString()
{
  if (str_)
  {
    delete [] str_;
  }
}

SuperString::SuperString(const SuperString& other) : str_(NULL)
{
  if (other.str_)
  {
    str_ = new char[strlen(other.str_)+1];
    strcpy(str_, other.str_);
  }
}

SuperString& SuperString::operator=(const SuperString& other)
{
  if (this != &other)
  {
    delete [] str_;
    if (other.str_)
    {
      str_ = new char[strlen(other.str_)+1];
      strcpy(str_, other.str_);
    }
  }
  return *this;
}

std::ostream& operator<<(std::ostream& os, const SuperString& str)
{
  os << str.str_;
  return os;
}

