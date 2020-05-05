#include <cstdlib>
#include <cstdio>

static void my_exit1(void);
static void my_exit2(void);
int main()
{
  if (atexit(my_exit1) != 0)
  {
    printf("register my_exit1 error\n");
    exit(-1);
  }
  if (atexit(my_exit2) != 0)
  {
    printf("register my_exit2 error\n");
    exit(-1);
  }
  printf("main done\n");
  return 0;
}



static void my_exit1(void)
{
  printf("first exit handler\n");
}

static void my_exit2(void)
{
  printf("second exit handler\n");
}
