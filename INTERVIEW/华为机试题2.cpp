#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>


using namespace std;


string repete_filter(string t);

int main()
{
	string t;
	cin >> t;
	
	cout << repete_filter(t);
	system("pause");
	return 0;
}

string repete_filter(string t)
{
	if (t.empty())
		return t;
	
	int tb[256];
	int len = t.size();
	for (int i=0; i<len; i++)
	{
		tb[t[i]] = 1;
	}
	
	string res;
	for (int i=0; i<256; i++)
	{
		if (tb[i] == 1)
		{
			res.push_back((char)i);
		}
	}
	return res;
}

