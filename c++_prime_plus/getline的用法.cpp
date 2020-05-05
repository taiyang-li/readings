#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main()
{	
	const int ArSize = 20;
	char name[ArSize];
	char dessert[ArSize];
	
	cout << "enter your name" << endl;
	cin.getline(name, ArSize);
	cout << "enter your favourite dessert" << endl;
	cin.getline(dessert, ArSize);
	cout << name << endl;
	cout << dessert << endl;
	
	system("pause");
	return 0;
}




