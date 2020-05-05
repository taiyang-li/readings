#include <unistd.h>
#include <cstdlib>
#include <cerrno>
#include <cstdio>
#include <sys/wait.h>

int my_system(const char* cmdstring)
{
  pid_t pid;
  int status;

  if (cmdstring == NULL)
    return (1);

  if ((pid = fork()) < 0)
    status = -1;
  else if (pid == 0)
  {
    execlp("/bin/bash", "bash", "-c", cmdstring, (char*)0);
    _exit(127);
  }
  else
  {
    while (waitpid(pid, &status, 0) < 0)
    {
      if (errno != EINTR)
      {
        status = -1;
        break;
      }
    }
  }
  printf("%s %d\n", cmdstring, status);
  return status;
}
int main()
{
  int status;
  if ((status = my_system("date")) != 0)
    printf("system date error\n");
  if ((status = my_system("nosuchcommand")) != 0)
    printf("system nosuchcommand error\n");
  if ((status = my_system("who; exit 44")) != 0)
    printf("system who exit error\n");
  return 0;
}
