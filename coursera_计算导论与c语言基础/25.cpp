#include <iostream>
#include <set>
using namespace std;

int main()
{
	int n, k;
	cin >> n >> k;

	set<int> s;
	for (int i=0; i<n; i++)
	{
		int tmp;
		cin >> tmp;
		s.insert(tmp);
	}

	for (set<int>::iterator it = s.begin(); it != s.end(); ++it)
	{
		if(s.find(k-*it) != s.end())
		{
			cout << "yes" << endl;
			return 0;
		}
	}
	cout << "no" << endl;
	return 0;
}
