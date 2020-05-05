#include <sys/time.h>
#include <cstdio>
#include <cstdlib>
#include <sys/types.h>
#include <unistd.h>
#include <ctime>

static void do_cmd(char* cmd);
static void pr_times(clock_t real, struct tms* tmsstart, struct tms* tmsend);

int main(int argc, char* argv[])
{
  int i;
  setbuf(stdout, NULL);
  for (i=0; i<argc; i++)
    do_cmd(argv[i]);
  return 0;
}

static void do_cmd(char* cmd)
{
  int status;
  clock_t start, end;
  struct tms tmsstart, tmsend;

  printf("command: %s\n", cmd);
  if ((start = times(&tmsstart)) == -1)
  {
    printf("times start error\n");
    exit(-1);
  }
  if ((status = system(cmd)) < 0)
  {
    printf("system error\n");
    exit(-1);
  }
  if ((end = times(&tmsend)) == -1)
  {
    printf("times end error\n");
    exit(-1);
  }
  pr_times(end-start, &tmsstart, &tmsend);
}

static void pr_times(clock_t real, struct tms* tmsstart, struct tms* tmsend)
{
  printf("real: %7.2f\n", (double)real/CLOCKS_PER_SEC);
  printf("user: %7.2f\n", (double)(tmsend->tms_utime - tmsstart->tms_utime)/CLOCKS_PER_SEC);
  printf("sys: %7.2f\n", (double)(tmsend->tms_stime - tmsstart->tms_stime)/CLOCKS_PER_SEC);
  printf("\tchild user: %7.2f\n", (double)(tmsend->tms_cutime - tmsstart->tms_cutime)/CLOCKS_PER_SEC );
  printf("\tchild sys: %7.2f\n", (double)(tmsend->tms_cstime - tmsstart->tms_cstime)/CLOCKS_PER_SEC );
}
