#include <iostream>
#include <sstream>
#include <string>
#include <cassert>
#include <map>
#include <cmath>
#include <cstdint>
using std::string;
using std::ostringstream;
using std::map;

int sgn(int n)
{
  if (n > 0)
    return 1;
  else if (n < 0)
    return -1;
  else
    return 0;
}

string doFractionToDecimal(int64_t numerator, int64_t denominator)
{
  assert(numerator > 0);
  assert(denominator > 0);

  ostringstream oss;
  map<int64_t, int> pos_by_dividend;
  int64_t divisor = denominator;
  int64_t dividend = numerator;
  int64_t quotient = dividend/divisor;
  int64_t remainder = dividend - quotient * divisor;
  oss << quotient;
  if (remainder == 0)
    return oss.str();
  
  oss << ".";
  int pos = oss.str().size();
  while (remainder != 0)
  {
    dividend = 10 * remainder;
    if (pos_by_dividend.count(dividend) != 0)
      break;

    quotient = dividend/divisor;
    remainder = dividend - quotient * divisor;
    oss << quotient;

    pos_by_dividend[dividend] = pos;
    pos++;
  }
  string ret = oss.str();
  if (remainder == 0)
    return ret;
  ret.insert(pos_by_dividend[dividend], "(");
  ret.append(")");
  return ret;
}

string fractionToDecimal(int numerator, int denominator)
{
  if (denominator == 0)
    return "error";

  if (numerator == 0)
    return "0";
  
  string ret_sgn = sgn(numerator)*sgn(denominator) > 0 ? "" : "-";
  int64_t new_numerator = (int64_t)numerator;
  int64_t new_denominator = (int64_t)denominator;
  return ret_sgn + doFractionToDecimal(abs(new_numerator), abs(new_denominator));
}

int main()
{
  std::cout << fractionToDecimal(1, 3) << std::endl;
  std::cout << fractionToDecimal(1, 9) << std::endl;
  std::cout << fractionToDecimal(11, 9) << std::endl;
  return 0;
}
