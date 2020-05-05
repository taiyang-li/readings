#include <iostream>
#include <string>
using namespace std;

int main()
{
	int n;
	cin >> n;

	string s;	
	if (n % 4 != 0)	
		s = "N";
	else if (n % 100 == 0 && n % 400 != 0)
		s = "N";
	else if (n % 3200 == 0)
		s = "N";
	else 
		s = "Y";

	cout << s << endl;
	return 0;
}
