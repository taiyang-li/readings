#include <iostream>
using namespace std;

int main()
{
	int n = 0;
	cin >> n;
	
	int ge, shi, bai;
	ge = n%10;
	shi = (n/10)%10;
	bai = n/100;

	cout << bai << endl;
	cout << shi << endl;
	cout << ge << endl;

	return 0;
}
