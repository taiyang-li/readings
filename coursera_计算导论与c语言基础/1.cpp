#include <iostream>
using namespace std;

int main()
{
	int NA[3] = {1, 3, 5};
	int today = 0;
	cin >> today;
	
	for (int i=0; i<3; i++)
	{
		if (today == NA[i])
		{
			cout << "NO" << endl;
			return 0;
		}
	}
	cout << "YES" << endl;
	return 0;
	
}
