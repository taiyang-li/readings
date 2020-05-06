#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
int main()
{
  int n = 0;
  int m = 0;
  cin >> n;
  cin >> m;

  int left = n;
  int cur_steps = 0;
  int pos = -1;
  vector<int> monkeys(n, 1);
  while (left > 1)
  {
    while (cur_steps < m)
    {
      pos = (pos + 1) % n;
      if (monkeys[pos] == 1)
        cur_steps++;
    }

    if (monkeys[pos] == 1)
    {
      // cout << pos + 1 << endl;
      monkeys[pos] = 0;
      cur_steps = 0;
      left--;
    }
  }
  vector<int>::iterator it = find(monkeys.begin(), monkeys.end(), 1);
  int king = 1+ (it - monkeys.begin());
  cout << king << endl;
  return 0;
}
