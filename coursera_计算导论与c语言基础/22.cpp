#include <iostream>
using namespace std;

int main()
{
	int a;
	int b[5];
	
	cin >> a;
	for (int i=0; i<5; i++)
	{
		cin >> b[i];
	}

	int sum = 0;
	for (int i=0; i<5; i++)
	{
		if(b[i] < a)
			sum += b[i];
	}

	cout << sum << endl;
	return 0;
}
