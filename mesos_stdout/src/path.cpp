#include "stout/path.hpp"
#include "stout/stringify.hpp"

int main()
{
  Path path("/../../data/liyang/workspace.tar.gz");
  std::cout << "basename: " << path.basename() << std::endl;
  std::cout << "dirname: " << path.dirname() << std::endl;
  std::cout << "extension: " << path.extension().get() << std::endl;
  std::cout << "isAbsolute: " << stringify(path.absolute()) << std::endl;
  return 0;
}
