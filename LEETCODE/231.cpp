#include <vector>
#include <iostream>
#include <algorithm>
#include <cmath>
#include "util.h"

bool isPowerOfTwo(int n)
{
  int64_t m = n;
  return (m != 0) && ! (m&(m-1));
}

int main()
{
  std::cout << ::stringify(isPowerOfTwo(100)) << std::endl;
  std::cout << ::stringify(isPowerOfTwo(2)) << std::endl;
  return 0;
}
