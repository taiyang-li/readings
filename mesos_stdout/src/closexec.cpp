#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <cstdio>
#include <cstdlib>
#include <stout/os/fcntl.hpp>

#define ERR_EXIT(msg) \
  do \
  { \
    perror(msg); \
    exit(-1); \
  } while(0)

int main()
{
  int fd = open("test.dat", O_RDWR | O_CREAT | O_TRUNC, 0644);
  if (fd < 0)
    ERR_EXIT("open file failed");

  auto ret = os::cloexec(fd);
  if (ret.isError())
    ERR_EXIT("set cloexec failed");

  char buf[32];
  sprintf(buf, "%d", fd);
  if (execl("/data/liyang/rhel6.2/build64_release/workspace/stout-test/readtest", "readtest", buf, NULL) < 0)
    ERR_EXIT("execl failed");
  return 0;
}
