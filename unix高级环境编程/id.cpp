#include <sys/types.h>
#include <unistd.h>
#include <cstdio>

int main()
{
  printf ("uid=%d, gid=%d\n", getuid(), getgid());
  return 0;
}
