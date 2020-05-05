#include <iostream>
#include <cstdlib>
#include <string>
#include <cstdio>
#include <algorithm>
#include <list> 
#include <vector>

using namespace std;

bool is_odd(int i) {return i%2==1;}
int main()
{
	int arr[4] = {1,3,4,10};
	vector<int> arr1(arr, arr+4);
	int count_res = count_if(arr1.begin(), arr1.end(), is_odd);
	cout << count_res << endl;
	system("pause");
	return 0;
}

