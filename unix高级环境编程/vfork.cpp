#include <sys/types.h>
#include <unistd.h>
#include <cstdio>
#include <cstdlib>

int glob = 6;

int main()
{
  int var;
  pid_t pid;
  
  var=88;
  printf("before vfork\n");
  if ((pid = vfork()) < 0)
  {
    printf("vfork error\n");
    exit(0);
  }
  else if (pid == 0)
  {
    glob++;
    var++;
    // 子进程和父进程共享进程空间，为了保证子进程不关闭文件流，此处使用_exit
    _exit(0);
  }
  sleep(1);
  printf("pid=%d, glob=%d, var=%d\n", getpid(), glob, var);
  return 0;
}
