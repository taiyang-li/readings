#include <iostream>
#include <ios>
#include <string>
#include <algorithm>
#include <functional>  
#include <fstream> 
#include <vector>
#include <cctype>

using namespace std;  	

 
bool is_huiwen(string &str); 
string del_nonalpha(string &str);
string to_upper(string &str);

int main()
{
	string str;
	cout << "enter a string" << endl;
	getline(cin, str);

	str = del_nonalpha(str);
	str = to_upper(str);

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

string del_nonalpha(string &str)
{	
	string res;	
	int len = str.size();
	if (len == 0)  return res;
	for (int i=0; i<len; i++)
	{ 
		if (isalnum(str[i]))
			res.push_back(str[i]);
	}
	return res;
}

string to_upper(string &str)
{
	string res;
	int len = str.size();
	if (len == 0) return res;
	for (int i=0; i<len; i++)
	{
		if (isalpha(str[i]))
			res.push_back(tolower(str[i]));
		else
			res.push_back(str[i]);
	}
	return res;
}








