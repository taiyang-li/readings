#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main()
{
	while(1)
	{
		int n;
		cin >> n;
		if (n == 0)
			break;

		vector<int> a(n, 0);
		for (int i=0; i<n; i++)
			cin >> a[i];

		sort(a.begin(), a.end());

		if (n % 2 == 0)
		{
			cout << (a[n/2] + a[n/2-1])/2 << endl;
		}
		else
		{
			cout << a[n/2] << endl;
		}
	}
	return 0;
}
