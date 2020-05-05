#include <iostream>
#include <base/utility/singleton_base.h>

class A 
{
  public:
    A() :  a(0) {} 

    int get_a()
    {
      return a;
    }

  private:
    int a;
};

class B : public A
{
  public:
    B() : b(0) {}

    int get_b()
    {
      return b;
    }
  private:
    int b;
};

class C : public A
{
  public:
    C() : c(0) {}

    int get_c()
    {
      return c;
    }
  private:
    int c;
};

int main()
{
  Biz::SingletonBase<C>::instance();
  Biz::SingletonBase<C>::instance();
  return 0;
}
