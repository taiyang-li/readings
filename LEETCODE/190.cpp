#include <cstdio>
#include <cstdint>
#include <iostream>

uint32_t reverseBits(uint32_t n)
{
  uint32_t ret = 0;
  for (int i=0; i<32; i++)
  {
    if (n & (1<<i))
      ret |= (1<<(32-1-i));
  }
  return ret;
}

int main ()
{
  std::cout << reverseBits(1) << std::endl;
  return 0;
}

