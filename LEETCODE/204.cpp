#include <cstdio>
#include <cstdlib>
#include <iostream>

#define SET_BITMAP(bitmap, n) (bitmap[(n-1)/8] |= (1<<(7-(n-1)%8)))
#define CLR_BITMAP(bitmap, n) (bitmap[(n-1)/8] &= (~(1<<(7-(n-1)%8))))
#define GET_BITMAP(bitmap, n) (bitmap[(n-1)/8] & (1<<(7-(n-1)%8)))

// count primes which is less or equal to n
int doCountPrimes(int n) 
{
  if (n <= 1)
    return 0;

  if (n == 2)
    return 1;

  char* bitmap = new char[(n+7)/8]();
  for (int i=2; i<=n; ++i)
  {
    if (GET_BITMAP(bitmap, i))
      continue;

    for (int j=2; ; ++j)
    {
      int tmp = i*j;
      if (tmp > n)
        break;
      SET_BITMAP(bitmap, tmp);
    }
  }

  int count = 0;
  for (int i=2; i<=n; ++i)
  {
    if (! GET_BITMAP(bitmap, i))
      count++;
  }
  delete [] bitmap;
  return count;
}

int countPrimes(int n)
{
  return doCountPrimes(n-1);
}

int main()
{
  std::cout << countPrimes(11) << std::endl;
  std::cout << countPrimes(10000) << std::endl;
  return 0;
}

