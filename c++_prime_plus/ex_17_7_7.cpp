#include <list>
#include <iterator>
#include <algorithm>
#include <iostream>
#include <string>
#include <iomanip>

using namespace std;  	

int main()
{
	string name;
	double wages;   
	double worked_hours;

	cout << "Enter your name: ";
	cin >> name;
	
	cout << "Enter your  hourly wages: ";
	cin >> wages;
	
	cout << "Enter number of hours worked: ";
	cin >> worked_hours;

	cout << "First format:" << endl;
	cout << setw(30) << name << ": $";
	cout << setprecision(2) << setw(20) << wages << ":";
	cout << setprecision(1) << setw(10) <<  fixed << worked_hours << endl;

	cout << "Second format:" << endl;
	cout << setw(30) << left << name << ": $";
	cout << setprecision(2) << left << setw(20) << wages << ":";
	cout << setprecision(1) << left << setw(10) << fixed << worked_hours << endl;
	
	system("pause");
	return 0;
}




