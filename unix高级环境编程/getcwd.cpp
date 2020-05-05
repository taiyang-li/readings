#include <unistd.h>
#include <cstdio>
#include <cstdlib>

int main()
{
  char *ptr;
  int size;
  if (chdir("/data/liyang") < 0)
    printf("chdir error\n");
  ptr = new char[256];
  if (getcwd(ptr, 256) == NULL)
  {
    printf("getcwd failed\n");
    exit(-1);
  }
  printf("cwd = %s\n", ptr);
  delete[] ptr;
  return 0;
}
