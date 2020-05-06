#include <cstdio>
#include <cstdint>
#include <cstdlib>
#include <set>
#include <iostream>

using std::set;

int64_t digit_square_sum(int64_t n)
{
  int ret = 0;
  int digit = 0;
  while (n)
  {
    digit = n % 10;
    ret += digit * digit;
    n /= 10;
  }
  return ret;
}

bool isHappy(int n)
{
  set<int64_t> history;
  history.insert(n);

  int64_t tmp = n;
  while (1)
  {
    tmp = digit_square_sum(tmp);
    if (history.find(tmp) != history.end())
      break;
    history.insert(tmp);
  }
  return tmp == 1;
}

int main(int argc, char* argv[])
{
  int n = atoi(argv[1]);
  if (isHappy(n))
    std::cout << "happy" << std::endl;
  else
    std::cout << "unhappy" << std::endl;
}
