#include <stout/os/environment.hpp>
#include <iostream>

int main()
{
  auto map = os::environment();
  for (const auto& kv: map)
    std::cout << "export " << kv.first << "=\"" << kv.second << "\"" << std::endl;
  return 0;
}
