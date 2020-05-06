#include <map>
#include <iostream>

using namespace std;

void add(map<int, int>& sum)
{
  int a = 0;
  int b = 0;
  while (cin >> a >> b && b >= 0)
  {
    if (sum.count(b) == 0)
      sum[b] = a;
    else
      sum[b] += a;
  }
}

void show(map<int, int>& sum)
{
  bool first = true;
  for (map<int, int>::reverse_iterator mit=sum.rbegin(); mit!=sum.rend(); ++mit)
  {
    if (mit->second == 0)
      continue;

    if (first)
      first = false;
    else
      cout << " ";

    cout << "[ " << mit->second << " " << mit->first << " ]";
  }
  cout << endl;
}

int main()
{
  int n = 0;
  cin >> n;
  for (int i=0; i<n; i++)
  {
    map<int, int> sum;
    add(sum);
    add(sum);
    show(sum);
  }
  return 0;
}
