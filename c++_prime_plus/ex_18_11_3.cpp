#include <iostream>
#include <cstdlib>
#include <string>
#include <cstdio>
#include <algorithm>
#include <list> 
#include <vector>
using namespace std;

double up(double x) {return 2.0*x;}
// void r1(const double &rx) {cout << rx << endl; cout << "const double &" << endl;}
void r1(double rx)  {cout << rx << endl; cout << "double &" << endl;} 
int main()
{
	double w = 10.0;
	
	r1(w);          // const double & 或者 double & 或 double皆可以 
	r1(w+1);        // const double &   表达式类型必须是 const double & 或者 double
	r1(up(w));      // const double &   函数返回值类型必须是 const double &  或者 double 
	system("pause");
	return 0;
}
