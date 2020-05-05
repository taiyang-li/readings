#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <cstdio>
#include <cstdlib>

int main(int argc, char* argv[])
{
  int i;
  struct stat buf;
  for (int i=1; i<argc; i++)
  {
    if (stat(argv[1], &buf) < 0)
    {
      printf("stat %s error\n", argv[1]);
      continue;
    }

    printf("dev=%d/%d\n", major(buf.st_dev), minor(buf.st_dev));
    if (S_ISCHR(buf.st_mode) || S_ISBLK(buf.st_mode))
    {
      printf("(%s) rdev=%d/%d\n", S_ISCHR(buf.st_mode) ? "charactor" : "block",
          major(buf.st_rdev), minor(buf.st_rdev));
    }
  }
  return 0;
}
