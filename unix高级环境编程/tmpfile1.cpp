#include <cstdio>
#include <cstdlib>

int main(int argc, char* argv[])
{
  if (argc != 3)
  {
    printf("Usage: a.out <directory> <prefix>\n");
    exit (-1);
  }

  printf("%s\n", tempnam(argv[1], argv[2]));
  return 0;
}
