#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string>
#include <iostream>

int main()
{
  // is dir?
  std::string path = "~/.vimrc";
  struct stat s;
}
