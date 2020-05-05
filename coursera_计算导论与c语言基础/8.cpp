#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main()
{
	int n;
	int tmp;
	vector<int> a;
	cin >> n;
	for (int i=0; i<n; i++)
	{
		cin >> tmp;
		a.push_back(tmp);
	}

	int max_score = 0;
	for (int i=0; i<n; i++)
	{
		max_score = max(max_score, a[i]);
	}
	
	cout << max_score << endl;
	return 0;
	
}
