#include <iostream>
#include <string>
using namespace std;

int main()
{
	string str, str1;
	while (cin >> str >> str1)
	{
		size_t len = str.size();
		char max_char = 0;
		for (int i=0; i<len; i++)
		{
			if (max_char < str[i])
				max_char = str[i];
		}

		size_t found = str.find(max_char);
		string left = str.substr(0, found+1);
		string right = str.substr(found+1);
		str = left + str1 + right;
		cout << str << endl;
	}
	return 0;
}
