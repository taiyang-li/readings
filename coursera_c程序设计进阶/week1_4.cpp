#include <ctime>
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <sstream>
#include <cstring>
#include <cstdio>

using namespace std;

string tomorrow()
{
  int year, month, day;
  scanf("%d-%d-%d", &year, &month, &day);
  struct tm tinfo;
  memset(&tinfo, 0, sizeof(tm));
  tinfo.tm_year = year- 1900;
  tinfo.tm_mon = month - 1;
  tinfo.tm_mday = day;
  
  time_t t = mktime(&tinfo);
  char tmp[64];
  t += 24*3600;
  strftime(tmp, 64, "%F", localtime(&t));
  return string(tmp);
}

int main()
{
  cout << tomorrow() << endl;
  return 0;
}
