#include <vector>
#include <string>
#include <iostream>

class A
{
  public:
  A(const std::string& name) : name_(name)
  {
    std::cout << "constructor1" << std::endl;
  }

  A(const A& other) : name_(other.name_)
  {
    std::cout << "constructor2" << std::endl;
  }

  ~A()
  {
    std::cout << "destructor" << std::endl;
  }

  private:
    std::string name_;
};

int main()
{
  std::vector<A> a;

  a.push_back(A("foo"));
  std::cout << "push back finish" << std::endl;

  a.emplace(a.begin(), "bar");
  std::cout << "emplace finish" << std::endl;

  std::cout << "to exit" << std::endl;
  return 0;
}
