#include <list>
#include <iterator>
#include <algorithm>
#include <iostream>
#include <string>
#include <iomanip>

using namespace std;  	

int main()
{
	char ch;
	int ct1 = 0;
	cin >> ch;
	while(ch  != 'q')            // 忽略空格和换行符
	{
		ct1++;
		cin >> ch;
	}
	cout << "ct1 done" << endl;
	
	int ct2 = 0;
	cin.get(ch);
	while (ch != 'q')            // 没有忽略空格和换行符
	{
		ct2++;
		cin.get(ch);
	}
	cout << "ct2 done" << endl;

	cout << "ct1 = " << ct1 << endl;
	cout << "ct2 = " << ct2 << endl;
	
	system("pause");
	return 0;
}




