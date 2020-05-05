#include <iostream>
#include <cstdlib>
#include <string>
#include <cstdio>
#include <algorithm>

using namespace std;

void my_print(int i) {cout << i << " ";}
int main()
{
	string str;
	cout << "enter the letter grouping (quit to quit): "; 
	while (cin >> str && str != "quit")
	{
		cout << "permutations of " << str << endl;
		sort(str.begin(), str.end());
		cout << str << endl;
		while(next_permutation(str.begin(), str.end()))
		{
			cout << str << endl;
		}
		cout << "enter the letter grouping (quit to quit): "; 
	}
	cout << "Done." << endl;
	system("pause");
	return 0;
}

 
