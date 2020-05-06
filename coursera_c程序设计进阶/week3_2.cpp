#include <cstdio>
#include <iostream>
using namespace std;

void guess(int n)
{
  if (n == 1)
  {
    cout << "End" << endl;
    return;
  }

  int tmp;
  if (n % 2 == 0)
  {
    tmp = n/2;
    cout << n << "/2=" << n/2 << endl; 
    guess(tmp);
  }
  else
  {
    tmp = 3*n + 1;
    cout << n << "*3+1=" << tmp << endl;
    guess(tmp);
  }
}

int main()
{
  int n;
  cin >> n;
  guess(n);
  return 0;
}
