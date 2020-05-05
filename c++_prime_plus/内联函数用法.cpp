#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <ctime>

using namespace std;



inline double square(double x) 
{
	return x*x;
}

int main()
{
	double a;
	double c = 13.0;

	a = square(5.0);
	cout << a << endl;

	system("pause");
	return 0;
}
