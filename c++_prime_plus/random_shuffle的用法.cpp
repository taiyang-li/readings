#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <string>
#include <memory>
#include <vector>
#include <algorithm>

using namespace std;

void my_function(int i) 
{
	cout << i << "\t";
}

int my_random(int i)
{
	return rand()%i;
}




int main()
{
	vector<int> tb;
	tb.push_back(10);
	tb.push_back(20);
	tb.push_back(30);
	tb.push_back(40);
	tb.push_back(50);
	tb.push_back(60);
	tb.push_back(70);
	
	for_each(tb.begin(), tb.end(), my_function);
	random_shuffle(tb.begin(), tb.end(), my_random);
	cout << endl;
	for_each(tb.begin(), tb.end(), my_function);

	system("pause");
	return 0;
}
