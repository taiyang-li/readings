#include <iostream>
#include <set>
using namespace std;

bool isZichu(int n)
{
	int t = n;
	int m = 0;
	while (t)
	{
		m += t%10;
		t /= 10;
	}
	return n%m == 0;
}
int main()
{
	int n = 0;
	cin >> n;
	for (int i=10; i<=n; i++)
	{
		if (isZichu(i))
			cout << i << endl;
	}
	return 0;
}
