#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <cstdio>
#include <cstdlib>
int main(int argc, char* argv[])
{
  if (argc != 2)
  {
    printf("usage: a.out <pathname>\n");
    exit(-1);
  }

  if (access(argv[1], R_OK) < 0)
    printf("access error\n");
  else
    printf("access success\n");

  if (open(argv[1], O_RDONLY) < 0)
    printf("open error\n");
  else
    printf("open success\n");

  return 0;
}

