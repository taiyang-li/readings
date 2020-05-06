#include <vector>
#include <iostream>
#include <algorithm>
#include <cmath>
#include "util.h"

bool isPowerOfTwo(int n)
{
  int count = 0;
  for (int i=2; i<n; ++i)
  {
    if (n % i == 0)
      count++;
  }
  return count % 2 == 1;
}

bool isPowerOfTwo1(int n)
{
  double curr = (double)n/2;
  double next = 0.0;
  double delta = n;
  while (delta > 1.0)
  {
    next = (curr*curr + n)/(2*curr);
    delta = (curr > next) ? (curr-next) : (next-curr);
    curr = next;
  } 
  int i = curr-delta;
  for (; i<=curr+delta; ++i)
    if (i*i == n)
      return true;
  return false;
}

int main()
{
  std::cout << ::stringify(isPowerOfTwo1(100)) << std::endl;
  std::cout << ::stringify(isPowerOfTwo1(101)) << std::endl;
  return 0;
}
