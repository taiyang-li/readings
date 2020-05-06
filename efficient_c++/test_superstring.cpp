#include "superstring.h"

int main()
{
  ::SuperString str1("helloworld");
  std::cout << str1 << std::endl;

  ::SuperString str2(str1);
  std::cout << str2 << std::endl;

  ::SuperString str3("byebye");
  str3 = str2;
  std::cout << str3 << std::endl;
  return 0;
}
