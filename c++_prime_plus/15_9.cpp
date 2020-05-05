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
		try 
		{
			z = hmean(x,y);
		}
		catch (const char *s)  // catched message was stores in const char *s
		{
			cout << s << endl;
			cout << "enter a new pair of numbers" << endl;
			continue;
		}	
		cout << "harmonic mean of " << x << " and " << y 
			<< " is " << z << endl;
	}
	return 0;
}



double hmean(double a, double b)
{
	if (a == -b)
		throw "bad hmean() arguments: a = -b not allowed";
	return 2.0*a*b/(a+b);
}

