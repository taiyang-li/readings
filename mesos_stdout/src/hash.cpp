#include <functional>
#include <string>
#include <iostream>
#include <map>

int main()
{
  std::hash<std::string> str_hash;
  std::string a = "foo";
  std::string b = "foo";
  std::string c = "bar";

  std::cout << (str_hash(a) == str_hash(b) ? "hash(a) == hash(b)" : "hash(a) != hash(b)") << std::endl;
  std::cout << (str_hash(a) == str_hash(c) ? "hash(a) == hash(c)" : "hash(a) != hash(c)") << std::endl;

  std::map<int, std::string> d;
  d.emplace(1, "one");
  for(auto mit : d)
  {
    std::cout << mit.first << ":" << mit.second << std::endl;
  }
  return 0;
}
