#include <cstdio>
#include <cstdlib>
int main()
{
  int c;
  while ((c = fgetc(stdin)) != EOF)
    if (fputc(c, stdout) == EOF)
    {
      printf("output error\n");
      exit(-1);
    }
  if (ferror(stdin))
  {
    printf("input error\n");
    exit(-1);
  }
  return 0;
}
