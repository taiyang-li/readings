#ifndef MONOMIAL_H
#define MONOMIAL_H

#include <string>
#include <iostream>
#include <sstream>
#include <list>

struct Monomial
{
    double _coefficient;
    std::string _var;
    double _power;

    Monomial(char expr)
    {
      if (expr >= '0' && expr <= '9')
      {
        _coefficient = expr - '0';
        _power = 0;
      }
      else
      {
        _coefficient = 1;
        _var = expr;
        _power = 1;
      }
    }

    std::string show()
    {
      std::ostringstream oss;
      if (_coefficient == 0)
      {
        oss << 0;
        return oss.str();
      }
      if (_power == 0)
      {
        oss << _coefficient;
        return oss.str();
      }
      if (_power == 1)
      {
        oss << _coefficient << "*" << _var;
        return oss.str();
      }
      oss << _coefficient << "*" << _var << "^" << _power;
      return oss.str();
    }
};

class Polynomial
{
  public:
    Polynomial();
};

#endif  /*MONOMIAL_H*/
