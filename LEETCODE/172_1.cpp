#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include <cstdint>
using std::vector;
using std::string;

int trailingZeroes(int n)
{
  int64_t i=5;
  int64_t count = 0;
  for (; n>=i; i*=5)
    count += (n/i);
  return count;
}

int trailingZeroes1(int n) {
      int result = 0;
          for(long long i=5; n/i>0; i*=5){
                    result += (n/i);
                        }
              return result;
}

int main()
{
  std::cout << trailingZeroes(1808548329) << std::endl;
  std::cout << trailingZeroes(1808548329) << std::endl;
  return 0;
}
