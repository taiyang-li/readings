#include <dirent.h>
#include <cstdio>
#include <unistd.h>
#include <cstdlib>

#define BUFFSIZE 1024
int main (int argc, char* argv[])
{
  int n;
  char buf[BUFFSIZE];

  while ( (n = read(STDIN_FILENO, buf, BUFFSIZE)) > 0)
  {
    if (write(STDIN_FILENO, buf, n) != n)
    {
      printf("write error\n");
    }
  }
  if (n < 0)
    printf("read error\n");
  return 0;
}
