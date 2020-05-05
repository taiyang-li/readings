#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <cstdio>
#include <cstdlib>
#include <stout/os/fcntl.hpp>
#include <stout/stringify.hpp>

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
  
  std::cout << stringify(os::isCloexec(fd).get()) << std::endl;
  return 0;
}
