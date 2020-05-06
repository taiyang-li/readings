#include "complex.h"

void test_complex1()
{
  Complex c1(1.0, 2.0);
  Complex c2(1.0, 3.0);
  Complex c3(1.0, 4.0);
  Complex c4 = c1 + c2 + c3;
}

void test_complex2()
{
  Complex c1(1.0, 2.0);
  Complex c2(1.0, 3.0);
  Complex c3(1.0, 4.0);
  Complex c4;
  c4 = c1 + c2 + c3;
}

int main()
{
  test_complex1();
  std::cout << "-----------------" << std::endl;
  test_complex2();
  return 0;
}
