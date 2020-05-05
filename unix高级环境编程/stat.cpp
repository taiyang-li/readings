#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <cstdio>

int main(int argc, char* argv[])
{
  struct stat buf;
  for (int i=1; i<argc; i++)
  {
    printf("file: %s\n", argv[i]);
    if (lstat(argv[1], &buf) < 0)
    {
      printf("lstat error\n");
      continue;
    }

    if (S_ISREG(buf.st_mode))
      printf("regular\n");
    else if (S_ISDIR(buf.st_mode))
      printf("isdir\n");
    else if (S_ISCHR(buf.st_mode))
      printf("character special\n");
    else if (S_ISBLK(buf.st_mode))
      printf("block special\n");
    else if (S_ISFIFO(buf.st_mode))
      printf("fifo\n");
    else if (S_ISLNK(buf.st_mode))
      printf("symbolic link\n");
    else if (S_ISSOCK(buf.st_mode))
      printf("socket\n");
    else 
      printf("unknown filetype\n");
  }
  return 0;
}

