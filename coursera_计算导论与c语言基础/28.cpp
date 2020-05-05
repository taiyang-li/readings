#include <iostream>
#include <cctype>
#include <algorithm>
#include <string>
#include <cstring>
using namespace std;

int main()
{
	string str1;
	string str2;
	cin >> str1;
	cin >> str2;
		
	transform(str1.begin(), str1.end(), str1.begin(), ::tolower);
	transform(str2.begin(), str2.end(), str2.begin(), ::tolower);
	
	int ret = strcmp(str1.c_str(), str2.c_str());
	if (ret < 0)
		cout << "<" << endl;
	else if (ret == 0)
		cout << "=" << endl;
	else 
		cout << ">" << endl;

	return 0;
}
