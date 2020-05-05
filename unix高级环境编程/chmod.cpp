#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <cstdio>
#include <cstdlib>

int main(int argc, char* argv[])
{
  struct stat statbuf;
  /* turn on set-group-id and turn off group-execute */
  if (stat("foo", &statbuf) < 0)
    printf("stat foo error\n");
  else if (chmod("foo", (statbuf.st_mode & ~S_IXGRP) | S_ISGID) < 0)
      printf("chmod foo error\n");

  /* set absolute mode to "rw-r--r--" */
  if (chmod("bar", S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH) < 0)
    printf("chmod bar error\n");
  return 0;
}
