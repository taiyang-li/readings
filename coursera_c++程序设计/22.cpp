#include <iostream>
#include <iomanip>

using namespace std;

int main()
{
	double a;
	cin >> a;

	cout.precision(5);
	cout << fixed << a << endl;

	cout.precision(7);
	cout << scientific << a << endl; 

	return 0;
}

