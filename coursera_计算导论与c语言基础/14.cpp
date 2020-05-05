#include <iostream>
#include <vector>
using namespace std;

int findKth(const vector<int>& a, int k)
{
	vector<int> flag;
	for (vector<int>::const_iterator it = a.begin(); it != a.end(); ++it)
	{
		flag.push_back(1);
	}
	
	for (int i=0; i<k; i++)
	{
		int max_num = 0;
		int max_idx = 0;

		for (int j=0; j<a.size(); j++)
		{
			if (flag[j] == 0)
			{
				continue;
			}

			if (max_num < a[j])
			{
				max_num = a[j];
				max_idx = j;
			}
		}
		flag[max_idx] = 0;
		if (i == k-1)
		{
			return a[max_idx];
		}
	}
	return -1;
}

int main()
{
	int n = 0;
	cin >> n;

	int k = 0;
	cin >> k;

	vector<int> a;
	int tmp;
	for (int i=0; i<n; i++)
	{
		cin >> tmp;
		a.push_back(tmp);
	}
	cout << findKth(a, k) << endl;
	return 0;
}
