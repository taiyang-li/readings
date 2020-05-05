#include <list>
#include <iostream>
#include <algorithm>

int main()
{
  std::list<int> a = {10, 100, 1000, 10000};
  for_each(begin(a), end(a), [](int n){std::cout << n << std::endl;});

  a.splice(end(a), a, begin(a));
  for_each(begin(a), end(a), [](int n){std::cout << n << std::endl;});
  return 0;
}
