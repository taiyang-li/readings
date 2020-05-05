#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <utime.h>
#include <unistd.h>
#include <cstdio>
#include <cstdlib>

int main(int argc, char* argv[])
{
  int i;
  int fd;
  struct stat statbuf;
  struct utimbuf timebuf;
  for (int i=1; i<argc; i++)
  {
    // stat 
    if (stat(argv[i], &statbuf) < 0)
    {
      printf("stat %s error\n", argv[i]);
      continue;
    }
    // open 
    if ( (fd = open(argv[i], O_RDWR | O_TRUNC)) < 0)
    {
      printf("open %s error\n", argv[i]);
      continue;
    }
    close(fd);
    // utime
    timebuf.actime = statbuf.st_atime;
    timebuf.modtime = statbuf.st_ctime;
    if (utime(argv[i], &timebuf) < 0)
    {
      printf("utime %s error", argv[i]);
      continue;
    }
  }
  exit(0);
}
