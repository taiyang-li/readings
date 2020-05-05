#include "stout/strings.hpp"
#include "stout/stringify.hpp"
#include <iostream>
#include <string>
#include <vector>

int main()
{
  // remove
  std::cout << "remove prefix: " << strings::remove("abcabcabc", "abc", strings::PREFIX) << std::endl;
  std::cout << "remove suffix: " << strings::remove("abcabcabc", "abc", strings::SUFFIX) << std::endl;
  std::cout << "remove any: " << strings::remove("abcabcabc", "abc", strings::ANY) << std::endl;

  // trim
  std::cout << "trim prefix: " << strings::trim(" \n\talhehf", strings::PREFIX) << std::endl;
  std::cout << "trim suffix: " << strings::trim("shdlhg\n\t ", strings::SUFFIX) << std::endl;
  std::cout << "trim any: " << strings::trim("\t\n shdlhg\n\t ", strings::ANY) << std::endl;

  // replace
  std::cout << "replace: " << strings::replace("helloworld", "hello", "goodbye") << std::endl;

  // tokenize
  auto tokenize_vec = strings::tokenize("a\t\tb\tc", "\t");
  for (const auto& x : tokenize_vec)
    std::cout << x << std::endl;

  // split(not different to tokenize)
  auto split_vec = strings::split("a\t\tb\tc", "\t");
  for (const auto& x : split_vec)
    std::cout << x << std::endl;

  // pair 
  auto pair_map = strings::pairs("foo=1;bar=2;baz;foo=3;bam=1=2", ";", "=");
  std::cout << stringify(pair_map) << std::endl;
  return 0;
}

