#include <unistd.h>
#include <fcntl.h>
#include <cstdio>
#include <cstdlib>
#include <cerrno>
#include <sys/types.h>
#include <sys/stat.h>

#define ERR_EXIT(msg) \
  do \
  { \
    perror(msg); \
    exit(-1); \
  } while(0)

void set_flag(int fd, int flags);
void clr_flag(int fd, int flags);

int main()
{
  char buf[1024];
  set_flag(0, O_NONBLOCK);
  int ret = read(0, buf, 1024);
  if (ret < 0)
    ERR_EXIT("read failed");
  return 0;
}

void set_flag(int fd, int flags)
{
  int val = fcntl(fd, F_GETFL, 0);
  if (val < 0)
    ERR_EXIT("get flag failed");
  val |= flags;
  if (fcntl(fd, F_SETFL, val) < 0)
    ERR_EXIT("set flag failed");
}

void clr_flag(int fd, int flags)
{
  int val = fcntl(fd, F_GETFL, 0);
  if (val < 0)
    ERR_EXIT("get flag failed");
  val &= ~flags;
  if (fcntl(fd, F_SETFL, val) < 0)
    ERR_EXIT("set flag failed");
}

