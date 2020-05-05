#include "stout/fs.hpp"
#include <iostream>
#include <string>

int main()
{
  std::string path = "/data/liyang";
  auto size = fs::size(path);
  std::cout << "size: " << size.get().kilobytes() << " kb" << std::endl;

  auto usage = fs::usage(path);
  std::cout << "usage: " << 100*usage.get() << "%" << std::endl;

  std::string origin = "./log.20160922";
  std::string link = "./log";
  auto ret1 = fs::symlink(origin, link);
  if (ret1.isSome())
    std::cout << "orgin: " << origin << ", link: "  << link << std::endl;

  std::string pattern = "./*.cpp";
  auto ret2 = fs::link(pattern);
  if (ret2.isSome())
  {
    for (std::string& file : ret2.get())
      std::cout << file << " ";
    std::cout << std::endl;
  }
  return 0;
}
