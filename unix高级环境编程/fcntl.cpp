#include <unistd.h>
#include <fcntl.h>
#include <cstdlib>
#include <cstdio>

int main(int argc, char* argv[])
{
  if (argc != 2)
  {
    printf("usage: a.out < descriptor#\n");
    exit(-1);
  }

  int val;
  if ((val = fcntl(atoi(argv[1]), F_GETFL, 0)) < 0)
  {
    printf("fcntl error for fd %d", atoi(argv[1]));
    exit(-1);
  }

  switch(val & O_ACCMODE)
  {
    case O_RDONLY:
      printf("read only\n");
      break;
    case O_WRONLY:
      printf("write only\n");
      break;
    case O_RDWR:
      printf("read write\n");
      break;
  }
  if (val & O_APPEND)
    printf("append\n");
  if (val & O_ASYNC)
    printf("async\n");
  if (val & O_DIRECT)
    printf("direct\n");
  if (val & O_NOATIME)
    printf("noatime\n");
  if (val & O_NONBLOCK)
    printf("nonblock\n");
  return 0;
}
