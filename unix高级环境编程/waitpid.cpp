#include <unistd.h>
#include <sys/wait.h>
#include <cstdio>
#include <cstdlib>

int main()
{
  pid_t pid;
  if ((pid = fork()) < 0)
  {
    printf("fork error\n");
    exit(-1);
  }
  else if (pid == 0)
  {
    if ((pid = fork()) < 0)
    {
      printf("fork error\n");
      exit(-1);
    }
    else if (pid > 0)
      exit(0);

    sleep(2);
    printf("second child, parent pid = %d\n", getppid());
    exit(0);
  }

  if (waitpid(pid, NULL, 0) != pid)
  {
    printf("waitpid error");
    exit(-1);
  }
  exit(0);
}
