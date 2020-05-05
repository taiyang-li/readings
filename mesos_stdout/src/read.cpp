#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <cstdio>
#include <cstdlib>

#define ERR_EXIT(msg) \
  do \
  { \
    perror(msg); \
    exit(-1); \
  } while(0)

int main(int argc, char* argv[])
{
  char buf[1024];
  int fd = atoi(argv[1]);
  if (read(fd, buf, 1024) < 0)
    ERR_EXIT("read file failed");
  return 0;
}
