#include <cstdio>
#include <iostream>
#include <sstream>

#define EXIT(status) __EXIT(status).stream() 

class __EXIT
{
  public:
    __EXIT(int status) : _status(status) {}

    ~__EXIT() 
    {
      std::cerr << _out.str() << std::endl;
    }

    std::ostream& stream()
    {
      return _out;
    }

  private:
    std::ostringstream _out;
    const int _status;
};

int main()
{
  EXIT(1) << "helloworld";
}
