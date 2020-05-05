#include <unistd.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>


int glob = 6;
char buf[] = "a write to stdout\n";

int main()
{
  int var;
  pid_t pid;

  var = 88;
  if (write(STDOUT_FILENO, buf, strlen(buf)) != (ssize_t)strlen(buf))
  {
    printf("write to stdout error\n");
    exit(-1);
  }
  
  printf("before fork\n");
  fflush(stdout);
  if ((pid = fork()) < 0)
  {
    printf("fork error\n");
    exit(-1);
  }
  else if (pid == 0)
  {
    glob++; var++;
  }
  else 
  {
    sleep(2);
  }
  printf("pid=%d, glob=%d, var=%d\n", pid, glob, var);
  exit(0);
}

