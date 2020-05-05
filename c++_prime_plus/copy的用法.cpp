#include <list>
#include <iterator>
#include <algorithm>
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;


void my_print(int i) {cout << i << " ";}
// 预定义函数符的用法
int main()
{
	int arr[8] = {1, 2, 3, 4, 5, 6, 7, 8};
	vector<int> arr1(8);
	copy(arr, arr+8, arr1.begin());
	for_each(arr1.begin(), arr1.end(), my_print);
	system("pause");
	return 0;
}
