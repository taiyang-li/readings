#include <cstdio>
#include <cstdlib>
int main()
{
  char name[1024];
  char line[1024];
  FILE* fp;

  printf("%s\n", tmpnam(NULL));
  tmpnam(name);
  printf("%s\n", name);

  if ((fp=tmpfile()) == NULL)
  {
    printf("tmpfile error\n");
    exit(-1);
  }
  fputs("one line of output\n", fp);
  rewind(fp);
  if (fgets(line, sizeof(line), fp) == NULL)
  {
    printf("fgets error\n");
    exit(-1);
  }
  fputs(line, stdout);
  return 0;
}
