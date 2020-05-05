#include <dirent.h>
#include <cstdio>
#include <unistd.h>
#include <cstdlib>

int main (int argc, char* argv[])
{
  DIR* dp;
  struct dirent *dirp;

  if (argc != 2)
  {
    printf("usage: ls directory_name");
    exit(-1);
  }

  if ((dp = opendir(argv[1])) == NULL)
  {
    printf("opendir %s failed\n", argv[1]);
    exit(-1);
  }

  while ((dirp = readdir(dp)) != NULL)
    printf("%s\n", dirp->d_name);
  return 0;
}
