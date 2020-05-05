#include <list>
#include <iterator>
#include <algorithm>
#include <iostream>
#include <string>
#include <iomanip>

using namespace std;  	

int main()
{
	int i;
	cout << "please input an interger" << endl;
	cin >> i;
	cout << dec << "base 10: " << setw(15) << i;
	cout << oct << "base 8: " << setw(15) << i;
	cout << hex << "base 16: " <<  setw(15) << i;
	system("pause");
	return 0;
}




