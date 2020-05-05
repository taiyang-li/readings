#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <string>
#include <memory>
#include <vector>
#include <algorithm>

using namespace std;


void my_function(int &i)
{
	cout << i << endl;
}

struct my_class 
{
	void operator ()(int i) {cout << i << "\t";} 
} my_object;



int main()
{
	vector<int> tb;
	tb.push_back(10);
	tb.push_back(20);
	tb.push_back(30);
	
	for_each(tb.begin(), tb.end(), my_function);  
	for_each(tb.begin(), tb.end(), my_object);
	
	system("pause");
	return 0;
}
