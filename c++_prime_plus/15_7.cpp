#include <iostream>
#include <cstdio>
#include <cstdlib>

using namespace std;

double hmean(double a, double b);

int main()
{
	double x,y,z;

	cout << "enter 2 numbers" << endl;
	while (cin >> x >> y)
	{
		hmean(x, y);	
		cout << "harmonic mean of " << x << " and " << y 
			<< " is " << z << endl;
	}
	return 0;
}



double hmean(double a, double b)
{
	if (a == -b) 
	{
		cout << "untenable arguments to hmean()" << endl;
		abort();
	}	
	return 2.0*a*b/(a+b);
}


