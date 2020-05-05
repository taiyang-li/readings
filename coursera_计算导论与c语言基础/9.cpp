#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdlib>
using namespace std;

int main()
{
	int tmp;
	int n = 6;
	vector<int> a;
	for (int i=0; i<n; i++)
	{
		cin >> tmp;
		a.push_back(tmp);
	}

	int max_odd = 0;
	int min_even = 100;
	for (int i=0; i<n; i++)
	{
		if (a[i] % 2 == 0)
		{
			min_even = min(min_even, a[i]);
		}
		else 
		{
			max_odd = max(max_odd, a[i]);
		}
	}
	cout << abs(max_odd - min_even) << endl;
	return 0;
	
}
