#include <list>
#include <iterator>
#include <algorithm>
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;


// 预定义函数符的用法
int main()
{
	const int LIM = 5;
	double arr1[LIM] = {36, 39, 42, 45, 48};
	vector<double> gr8(arr1, arr1+LIM);
	ostream_iterator<double> out(cout, " ");
	copy(gr8.begin(), gr8.end(), out);
	// transform(gr8.begin(), gr8.end(), out, sqrt);
	system("pause");
	return 0;
}
