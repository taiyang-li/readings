
#include <boost/variant.hpp> 
#include <boost/any.hpp> 
#include <vector> 
#include <string> 
#include <iostream> 

std::vector<boost::any> vector; 

struct output : 
  public boost::static_visitor<> 
{ 
  void operator()(double &d) const 
  { 
    vector.push_back(d); 
  } 

  void operator()(char &c) const 
  { 
    vector.push_back(c); 
  } 

  void operator()(std::string &s) const 
  { 
    vector.push_back(s); 
  } 
}; 

int main() 
{ 
  boost::variant<double, char, std::string> v; 
  v = 3.14; 
  boost::apply_visitor(output(), v); 
  v = 'A'; 
  boost::apply_visitor(output(), v); 
  v = "Hello, world!"; 
  boost::apply_visitor(output(), v); 

  return 0;
}
