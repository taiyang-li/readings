#include "stout/duration.hpp"

int main()
{
  // Duration::Duration
  Duration a;
  std::cout << a << std::endl;
  timeval t;
  t.tv_sec = 1000;
  t.tv_usec = 10000;
  Duration b(t);
  std::cout << b << std::endl;
  t = b.timeval();
  std::cout << "sec: " << t.tv_sec << ", usec: " << t.tv_usec << std::endl;
  
  // Duration::ns ms secs mins hrs days weeks
  std::cout << "in ns: " << b.ns() << std::endl;
  std::cout << "in ms: " << b.ms() << std::endl; 
  std::cout << "in secs: " << b.secs() << std::endl;
  std::cout << "in mins: " << b.mins() << std::endl;
  std::cout << "in hrs: " << b.hrs() << std::endl;
  std::cout << "in days: " << b.days() << std::endl;
  std::cout << "in weeks: " << b.weeks() << std::endl;

  // Duration::parse
  return 0;
}
