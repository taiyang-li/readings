#include <string>
#include <iostream>
#include <cstring>
#include <cstdint>
#include <cstdio>

char buf[1024];

struct A
{
  uint32_t a:4;
  uint32_t b:4;
  uint32_t c:24;
  char d[4];
  uint32_t e;

  void pr()
  {
    printf("%d %d %d %s %d\n", a, b, c, d, e);
  }
};

void foo()
{
  A* ptr = (A*)buf;
  ptr->a = 1;
  ptr->b = 2;
  ptr->c = 3;
  strcpy(ptr->d, "abc");
  ptr->e = 4;

  A tmp;
  memcpy((void*)&tmp, (void*)buf, sizeof(A));
  tmp.pr();
}


int main()
{
  foo();
  return 0;
}
