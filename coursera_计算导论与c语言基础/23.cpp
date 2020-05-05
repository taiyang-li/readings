#include <iostream>
using namespace std;

int unlockTime = 27;
int lockTime = 23;
float getBikeTime(int n)
{
	return unlockTime + float(n)/3.0 + lockTime;	
}

float getWalkTime(int n)
{
	return float(n)/1.2;
}

int main()
{
	int n;
	while(cin >> n)
	{
		if (getBikeTime(n) > getWalkTime(n))
		{
			cout << "Walk" << endl;
		}
		else if (getBikeTime(n) == getWalkTime(n))
		{
			cout << "All" << endl;
		}
		else
		{
			cout << "Bike" << endl;
		}
	}
	return 0;
}
