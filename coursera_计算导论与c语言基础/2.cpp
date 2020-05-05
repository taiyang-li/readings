#include <iostream>
#include <string>

using namespace std;

int main()
{
	int m = 0;
	int n = 0;
	cin >> m >> n;

	int sum = 0;
	for (int i=m; i<=n; i++)
	{
		if (i%2 == 1)
		{
			sum += i;
		}
	}
	cout << sum << endl;
	return 0;
}
