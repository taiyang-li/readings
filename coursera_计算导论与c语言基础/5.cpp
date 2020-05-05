#include <iostream>
using namespace std;

int main()
{
	int k;
	cin >> k;

	int a[100];
	for (int i=0; i<k; i++)
	{
		cin >> a[i];
	}

	for (int i=k-1; i>=0; i--)
	{
		cout << a[i];
		if (i)
			cout << " ";
	}
	cout << endl;
	return 0;
}
