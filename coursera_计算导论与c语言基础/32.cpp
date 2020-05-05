#include <iostream>
#include <vector>
using namespace std;

void shiftByM(vector<int>& in, vector<int>& out, int n, int m)
{
	for (int i=0; i<n; i++)
	{
		out[(i+m)%n] = in[i];
	}
}

int main()
{	
	int n, m;
	vector<int> a(n, 0);

	cin >> n >> m;
	for(int i=0; i<n; i++)
	{
		cin >> a[i];
	}

	vector<int> b(a);	
	shiftByM(a, b, n, m);

	for(int i=0; i<n; i++)
	{
		cout << b[i] << " ";
	}
	cout << endl;
	return 0;
}
