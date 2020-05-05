#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <cstdio>
#include <functional>
using namespace std;

class A
{
  public:
    void pr_msg(const string& msg)
    {
      cout << msg << endl;
    }
};
int main()
{
  vector<string> str_vec;
  vector<string*> str_ptr_vec;

  char tmp[10];
  for (int i=0; i<100; i++)
  {
    sprintf(tmp, "%d", i);
    str_vec.push_back(string(tmp));
  }

  for (vector<string>::iterator it=str_vec.begin(); it!=str_vec.end(); ++it)
  {
    str_ptr_vec.push_back(&(*it));
  }

  for (vector<string*>::iterator it=str_ptr_vec.begin(); it!=str_ptr_vec.end(); ++it)
  {
    std::cout << **it << std::endl;
  }

  A a;
  for_each(str_ptr_vec.begin(), str_ptr_vec.end(), mem_fun(bind1st(&A::pr_msg, &a)));
  return 0;
}
