#include <iostream>
#include <ios>
#include <string>
#include <algorithm>
#include <functional>  
#include <fstream> 
#include <vector>

using namespace std;  	

bool is_huiwen(string &str); 

int main()
{
	string str;
	cout << "enter a string" << endl;
	cin >> str;
	if (is_huiwen(str))
		cout << str << " is a huiwen" << endl;
	else
		cout << str <<  " is not a huiwen" << endl;
	system("pause");
	return 0;
}

bool is_huiwen(string &str) 
{
	string temp(str);
	reverse(temp.begin(), temp.end());
	return str == temp;
}





