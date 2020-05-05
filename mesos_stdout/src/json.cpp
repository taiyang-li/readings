#include "stout/json.hpp"
#include <iostream>

int main()
{
  std::string str = "{\"name\":\"limoumou\",\"age\":25}";
  Try<JSON::Object> json = JSON::parse<JSON::Object>(str);
  if (json.isSome())
  {
    std::cout << "name: " << json.get().at<JSON::String>("name").get().value << std::endl;
    std::cout << "age: " << json.get().at<JSON::String>("age").get().value << std::endl;
  }
  return 0;
}
