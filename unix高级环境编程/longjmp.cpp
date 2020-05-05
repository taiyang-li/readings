#include <csetjmp>
#include <cstdio>
#include <cstdlib>

static void f1(int i, int j, int k, int l);
static void f2();
static jmp_buf jmpbuffer;
static int globval;

int main()
{
  int autoval;
  register_t regival;
  volatile int volaval;
  static int statval;

  globval = 1;
  autoval = 2; 
  regival = 3;
  volaval = 4;
  statval = 5;

  if (::setjmp(jmpbuffer) != 0)
  {
    printf("after longjmp\n");
    printf("globval=%d, autoval=%d, regival=%d, volaval=%d, statval=%d\n", 
        globval, autoval, regival, volaval, statval);
    exit(0);
  }

  globval = 91;
  autoval = 92;
  regival = 93;
  volaval = 94;
  statval = 95;
  f1(autoval, regival, volaval, statval);
  exit(0);
}

static void f1(int i, int j, int k, int l)
{
  printf("in f1()\n");
  printf("globval=%d, autoval=%d, regival=%d, volaval=%d, statval=%d\n", 
      globval, i, j, k, l);
  f2();
}
static void f2()
{
  longjmp(jmpbuffer, 1);
}

