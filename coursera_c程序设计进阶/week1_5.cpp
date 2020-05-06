#include <vector>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Info
{
  int id;
  float rate;
  Info(int n, float f) : id(n), rate(f) {}
};

bool compare(const Info& a, const Info& b)
{
  return a.rate < b.rate;
}

int main()
{
  vector<Info> rates(100, Info(0, 0.0));
  int n;
  cin >> n;
  float ave = 0.0;
  for (int i=0; i<n; ++i)
  {
    int id, before, after;
    cin >> id >> before >> after;
    rates[i].id = id;
    rates[i].rate = (float)after/before;
    ave += rates[id-1].rate;
  }

  ave /= n;
  sort(rates.begin(), rates.begin()+n, compare);

  int A_count;
  int B_count;
  vector<Info>::iterator it = std::lower_bound(rates.begin(), rates.begin()+n, Info(-1, ave), compare);
  B_count = it-rates.begin();
  A_count = n - B_count;
  cout <<  A_count << endl;
  for (int i=B_count; i<n; i++)
    cout << rates[i].id << endl;
  cout <<  B_count << endl;
  for (int i=0; i<B_count; i++)
    cout << rates[i].id << endl;
  return 0;
}
