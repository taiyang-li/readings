#include <iostream>
#include <cstdlib>
#include <string>
#include <cstdio>
#include <algorithm>
#include <list> 
#include <vector>
#include <array>
#include <initializer_list>
using namespace std;

template<class T>
T average_list(initializer_list<T> &a);

int main()
{
	double a[3] = {15.4, 10.7, 9.0};
	initializer_list<double> a1(a, a+3);
	auto q = average_list(a1);
	cout << q << endl; 
	system("pause");
	return 0;
}

template<class T>
T average_list(initializer_list<T> &a)
{
	T res = 0;
	for (auto it=a.begin(); it!=a.end(); ++it)
		res += *it;
	return res;
}




