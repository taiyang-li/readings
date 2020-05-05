#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
using namespace std;

const int R = 5;
const int C = 5;

int swapLine(int* arr, int n, int m)
{
	if (n < 0 || n >= R || m < 0 || m > R)
		return 0;

	if (n == m)
		return 1;

	int tmp;
	for (int i=0; i<C; i++)
	{
		tmp = *(arr + n * C + i);
		*(arr + n * C + i) = *(arr + m * C + i);
		*(arr + m * C + i) = tmp;
	}
	return 1;
}

int main()
{	
	int a[R][C];
	int n, m;
	for (int i=0; i<R; i++)
	{
		for (int j=0; j<C; j++)
		{
			cin >> a[i][j];
		}
	}
	cin >> n >> m;

	int ret = swapLine(a[0], n, m);
	if (ret == 0)
	{
		cout << "error" << endl;
		return 0;
	}
	
	for (int i=0; i<R; i++)
	{
		for (int j=0; j<C; j++)
		{
			cout << setw(4) << a[i][j];

			if (j == C-1)
				cout << endl;
		}
	}
	return 0;
}
