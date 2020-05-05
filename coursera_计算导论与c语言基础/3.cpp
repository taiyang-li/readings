#include <iostream>
using namespace std;

int main()
{	
	int k;
	int num[100];
	int count1 = 0;
	int count5 = 0; 
	int count10 = 0;
	
	cin >> k;
	for (int i=0; i<k; i++)
	{
		cin >> num[i];
	}
	
	for (int i=0; i<k; i++)
	{
		if (num[i] == 1)
			count1++;
		if (num[i] == 5)
			count5++;
		if (num[i] == 10)
			count10++;
	}
	
	cout << count1 << endl;
	cout << count5 << endl;
	cout << count10 << endl;

	return 0;
}
