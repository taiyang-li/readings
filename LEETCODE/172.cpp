#include <iostream>
#include <string>
#include <vector>
#include <cassert>
using std::vector;
using std::string;

int exponent(int n, int base)
{
  assert(n >= 1);
  int count = 0;
  while (n % base == 0)
  {
    count++;
    n /= base;
  }
  return count;
}

int trailingZeroes(int n)
{
  int sum_exp2 = 0;
  int sum_exp5 = 0;
  for (int i=2; i<=n; i++)
  {
    sum_exp2 += exponent(i, 2);
    sum_exp5 += exponent(i, 5);
  }
  return sum_exp5 > sum_exp2 ? sum_exp2 : sum_exp5;
}

int main()
{
  std::cout << trailingZeroes(1808548329) << std::endl;
  return 0;
}


