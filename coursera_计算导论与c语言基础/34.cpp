#include <iostream>
#include <vector>
#include <utility>
using namespace std;

int main()
{
	int L = 0;
	int M = 0;
	cin >> L >> M;

	vector<pair<int, int> > occupy(L, pair<int, int>(0, 0));
	for (int i=0; i<M; i++)
	{
		cin >> occupy[i].first >> occupy[i].second;
	}
	
	vector<int> a(L+1, 1);
	for (int i=0; i<M; i++)
	{
		for (int j=occupy[i].first; j<=occupy[i].second; j++)
		{
			a[j] = 0;
		}
	}

	int count = 0;
	for (int i=0; i<L+1; i++)
	{
		count += a[i];
	}
	
	cout << count << endl;
	return 0;
}
