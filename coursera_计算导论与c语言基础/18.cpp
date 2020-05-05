#include <iostream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

int main()
{
	int n = 0;
	int a[3] = {3, 5, 7};
	int b[3] = {0};
	vector<string> result;
	while (cin >> n)
	{
		if (!cin.good())
			break;
		int total = 0;
		ostringstream oss;
		for(int i=0; i<3; i++)
		{
			if (n % a[i] == 0)
			{
				b[i] = 1;
				total += 1;
				oss << a[i] << " "; 
			}
		}

		if (oss.str().empty())
		{
			// result.push_back("n");
			cout << "n" << endl;
		}
		else
		{
			// result.push_back(oss.str());
			cout << oss.str() << endl;
		}
	}

	/*
	for(vector<string>::iterator it = result.begin(); it != result.end(); it++)
	{
		cout << *it << endl;
	}
	*/
	return 0;
}
