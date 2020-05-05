#include <iostream>
#include <vector>
using namespace std;

bool isBad(vector<vector<int> >& arr, int i, int j)
{
	int tmp = arr[i][j] + 50;
	return tmp <=arr[i-1][j] && tmp <= arr[i+1][j] && tmp <= arr[i][j-1] && tmp <= arr[i][j+1] ;
}

int main()
{	
	int n = 0;
	cin >> n;

	vector<vector<int> > arr(n, vector<int>(n, 0));
	for (int i=0; i<n; i++)
		for (int j=0; j<n; j++)
			cin >> arr[i][j];
	
	int badCount = 0;
	for (int i=1; i<n-1; i++)
	{
		for (int j=1; j<n-1; j++)
		{
			if (isBad(arr, i, j))
				badCount++;
		}
	}
	cout << badCount << endl;
	return 0;
}
