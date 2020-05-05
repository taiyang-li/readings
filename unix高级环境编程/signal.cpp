#include <unistd.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>

#define BUFFSIZE 1024

static void sig_int(int sig);
int main()
{
  int status;
  pid_t pid;
  char buf[BUFFSIZE];

  if (signal(SIGINT, sig_int) == SIG_ERR)
  {
    printf("signal error\n");
    exit(-1);
  }

  printf("%% ");
  while (fgets(buf, BUFFSIZE, stdin) != NULL)
  {
    if (buf[strlen(buf)-1] == '\n')
      buf[strlen(buf)-1] = 0;

    if ((pid = fork()) < 0)
    {
      printf("fork error\n");
    }
    /* child process */
    else if (pid == 0)
    {
      execlp(buf, buf, (char*)0);
      printf("could not execute %s\n", buf);
      exit(-1);
    }
    
    /* father process */
    if ((pid = waitpid(pid, &status, 0)) < 0)
    {
      printf("waitpid error\n");
    }
    printf("%% ");
  }
  return 0;
}

void sig_int(int sig)
{
  printf("interrupt\n");
}
