#include <cstdint>
#include <cstdio>
#include <cinttypes>

int main()
{
  uint64_t a = ((uint64_t)1) << 63;
  printf("test uint64_t %lu\n", (unsigned long)a);
  printf("%ld %ld\n", sizeof(unsigned long), sizeof(unsigned long long));
  return 0;
}
