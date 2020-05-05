#include "stout/stringify.hpp"
#include "stout/hashmap.hpp"
#include "stout/hashset.hpp"
#include <iostream>
#include <set>
#include <list>
#include <vector>
#include <string>
#include <map>

int main()
{
  // common type
  float a = 3.1415;
  std::cout << stringify<float>(a) << std::endl;

  // bool 
  bool b = false;
  std::cout << stringify(b) << std::endl;

  // set 
  std::set<int> c = {1, 2, 3};
  std::cout << stringify<int>(c) << std::endl;

  // list 
  std::list<int> d = {1, 2, 3};
  std::cout << stringify<int>(d) << std::endl;

  // vector
  std::vector<int> e = {1,2,3};
  std::cout << stringify<int>(e) << std::endl;

  // map 
  std::map<int, std::string> f = {{1, "one"}, {2, "two"}, {3, "three"}};
  std::cout << stringify<int, std::string>(f) << std::endl;

  // hashset 
  hashset<int> g = {1,2,3};
  std::cout << stringify<int>(g) << std::endl;

  // hashmap 
  hashmap<int, std::string> h = {{1, "one"}, {2, "two"}, {3, "three"}};
  std::cout << stringify<int, std::string>(h) << std::endl;
  return 0;
}
