#include <iostream>
#include <cstdlib>
#include <string>
#include <cstdio>
#include <algorithm>
#include <list> 
#include <vector>

using namespace std;

template<class T>
void show2(double x, T& fp) 
{
	cout << x << "->" << fp(x) << endl;
}

int main()
{
	show2(18.0, [](double x) {return 32+1.8*x;});
	system("pause");
	return 0;
}

