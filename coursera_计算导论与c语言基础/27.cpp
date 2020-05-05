#include <iostream>
#include <set>
using namespace std;

int main()
{
	int count[256] = {0};
	string line;
	getline(cin, line);
	
	for(int i=0; i<line.size(); i++)
	{
		count[line[i]]++;
	}
	
	cout << count['a'] << " ";
	cout << count['e'] << " ";
	cout << count['i'] << " ";
	cout << count['o'] << " ";
	cout << count['u'] << endl;
	return 0;
}
