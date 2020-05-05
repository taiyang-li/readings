#include <fcntl.h>
#include <unistd.h>
#include <cstring>
#include <cstdio>
#include <cstdlib>

#define ERR_EXIT(msg) \
  do \
  { \
    perror(msg); \
    exit(-1); \
  } while(0)

int main()
{
  int fd = open("test.dat", O_CREAT | O_RDWR | O_TRUNC, 0644);
  if (fd < 0)
    ERR_EXIT("open file failed");

  struct flock f;
  memset(&f, 0, sizeof(f));
  f.l_type = F_WRLCK;
  f.l_whence = SEEK_SET;
  f.l_start = 0;
  f.l_len = 0;

  if (fcntl(fd, F_SETLK, &f) < 0)
    ERR_EXIT("lock file failed");

  printf("press any key to unlock\n");
  getchar();
  f.l_type = F_UNLCK;
  if (fcntl(fd, F_SETLK, &f) < 0)
    ERR_EXIT("unlock file failed");
  return 0;
}
