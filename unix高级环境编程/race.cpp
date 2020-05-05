#include <cstdio>
#include <cstdlib>
#include <sys/wait.h>
#include <unistd.h>

static void charatatime(char* );

int main()
{
  pid_t pid;
  if ((pid = fork()) < 0)
  {
    printf("fork error\n");
    exit(-1);
  }
  else if (pid == 0)
    charatatime((char*)"output from child\n");
  else 
    charatatime((char*)"output from parent\n");
  exit(0);
}

static void charatatime(char* str)
{
  char* ptr;
  int c;
  setbuf(stdout, NULL);
  for (ptr = str; (c=*ptr++) != 0; )
    fputc(c, stdout);
}
