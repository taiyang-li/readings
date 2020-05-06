#include <vector>
#include <sstream>
#include <string>
#include <cstdlib>

template <typename T>
std::string stringify(T t)
{
  std::ostringstream out;
  out << t;
  if (!out.good()) {
    abort();
  }
  return out.str();
}

template <>
inline std::string stringify(bool b)
{
  return b ? "true" : "false";
}


template <typename T>
std::string stringify(const std::vector<T>& vector)
{
  std::ostringstream out;
  out << "[ ";
  typename std::vector<T>::const_iterator iterator = vector.begin();
  while (iterator != vector.end()) {
    out << stringify(*iterator);
    if (++iterator != vector.end()) {
      out << ", ";
    }   
  }
  out << " ]";
  return out.str();
}
