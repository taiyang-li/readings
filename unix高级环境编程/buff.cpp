#include <cstdio>
#include <cstring>
#include <cstdlib>

void pr_stdio(const char* name, FILE* fp);

int main()
{
  FILE* fp;
  fputs("enter any characters\n", stdout);
  if (getchar() == EOF)
  {
    printf("getchar error\n");
    exit(-1);
  }
  fputs("one line to stderr\n", stderr);

  pr_stdio("stdin", stdin);
  pr_stdio("stdout", stdout);
  pr_stdio("stderr", stderr);

  if ((fp=fopen("/etc/motd", "r")) == NULL)
  {
    printf("fopen error\n");
    exit(-1);
  }
  if (fgetc(fp) == EOF)
  {
    printf("fgetc error\n");
    exit(-1);
  }
  pr_stdio("/etc/motd", fp);
  return 0;
}


void pr_stdio(const char* name, FILE* fp)
{
  printf("stream = %s, ", name);

 // not portable
 if (fp->_IO_file_flags & _IO_UNBUFFERED)
   printf("unbuffered");
 else if (fp->_IO_file_flags & _IO_LINE_BUF)
   printf("line buffered");
 else 
   printf("fully buffered");
 printf(", buffer size = %d\n", fp->_IO_buf_end - fp->_IO_buf_base);
}
