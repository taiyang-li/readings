#include <iostream>
#include <cstdlib>
#include <string>
#include <cstdio>
#include <algorithm>
#include <list> 
#include <vector>
using namespace std;

double up(double x) {return 2.0*x;}
void r1(double &rx)  {cout << rx << endl; cout << "double &" << endl;} 
void r1(double	&&rx) {cout << rx << endl; cout << "double &&" << endl;} 
int main()
{
	double w = 10.0;
	
	r1(w);           //  double &
	r1(w+1);         //  double &&
	r1(up(w));       //  double &&
	return 0;
}
