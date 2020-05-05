#include <iostream>
#include <cstdlib>
#include <string>
#include <cstdio>
#include <algorithm>
#include <list> 
#include <vector>
using namespace std;

double up(double x) {return 2.0*x;}
void r1(const double &rx) {cout << rx << endl;}
void r2(double &rx) {cout << rx << endl;}
void r3(double &&rx) {cout << rx << endl;} 

int main()
{
	double w = 10.0;
	r1(w);
	r1(w+1);
	r1(up(w)); 
	
	r2(w);
	r2(w+1);         // 因为w+1是表达式，所以不能转化为引用类型
	r2(up(w));       // up(w)是函数返回值，临时变量，所以不能转化为引用类型  
	
	r3(w);           // 双层引用 不懂     
	r3(w+1);
	r3(up(w));
	
	system("pause");
	return 0;
}
