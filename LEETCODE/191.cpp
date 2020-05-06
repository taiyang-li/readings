#include <iostream>
#include <cstdint>


int hammingWeight(uint32_t n)
{
  int i=0;
  int ret = 0;
  while (n)
  {
    if (n & 1)
      ret++;
    n = n >> 1;
  }
  return ret;
}

int main()
{
  std::cout << hammingWeight(64-1) << std::endl;
  return 0;
}
