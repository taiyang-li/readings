#include <iostream>
#include <vector>
using namespace std;

int count_one(int n);
int main()
{
	int len;
	cin >> len;
	
	vector<int> num;
	for (int i=0; i<len; i++)
	{
		int tmp;
		cin >> tmp;
		num.push_back(tmp);
	}
	
	for (int i=0; i<len; i++)
	{
		cout << count_one(num[i]) << endl;
	}

	return 0;
}

int count_one(int n)
{
	int ret = 0;

	while (n)
	{
		if (n % 2 == 1)
			ret++;

		n /= 2;
	}
	return ret;
}

