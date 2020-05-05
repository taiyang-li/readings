#include <iostream>
using namespace std;

int main()
{
	int a[6] = {100, 50, 20, 10, 5, 1};
	int b[6] = {0};
	int v = 0;
	cin >> v;

	for (int i=0; i<6; i++)
	{
		b[i] = v/a[i];
		v -= b[i] * a[i];
		cout << b[i] << endl;
	}
	
	return 0;
}
