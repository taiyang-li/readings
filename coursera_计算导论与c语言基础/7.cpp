#include <iostream>
#include <cmath>
using namespace std;

int main()
{
	float total = 20;
	float h = 0.0; 
	float r = 0.0;
	float pi = 3.14159;
	cin >> h >> r;

	h /= 10;
	r /= 10;
	float volumn = pi * r * r * h;
	
	int n = int(ceil(total/volumn));
	cout << n << endl;
	return 0;
}
