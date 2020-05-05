#include <sys/time.h>
#include <ctime>
#include <iostream>

int main()
{
  struct timeval tv[2];
  ::utimes("/root/ycm_init.sh", tv);
  std::cout << "access time: " << ctime(&tv[0].tv_sec);
  std::cout << "modification time: " << ctime(&tv[1].tv_sec);
  return 0;
}
