#include <iostream>
#include <cstdlib>
#include <string>
#include <cstdio>
#include <algorithm>
#include <list> 
#include <vector>
#include <array>
using namespace std;

const int Size = 5;
template<class T>
void sum(array<double, Size> a, T& fp); 

int main()
{
	static double total = 0.0;
	array<double, Size> temp_c = {32.1, 34.3, 37.8, 34.7, 89.3};
	sum(temp_c, [](double x){total += x;});
	cout << total << endl;
	system("pause");
	return 0;
}

template<class T>
void sum(array<double, Size> a, T& fp)
{
	int n = 0;
	for (auto pt=a.begin(); pt!=a.end(); ++pt)
		fp(*pt);
}




