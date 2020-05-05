#include <unistd.h>
#include <cstdio>
#include <cstdlib>

int main()
{
  if (chdir("/data/liyang") < 0)
    printf("chdir error\n");
  printf("chdir success\n");
  return 0;
}
