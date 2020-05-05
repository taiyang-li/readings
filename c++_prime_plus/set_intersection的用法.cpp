#include <list>
#include <iterator>
#include <algorithm>
#include <iostream>
#include <vector> 
#include <cmath>  
#include <functional>
 
using namespace std;

void my_print(int i) {cout << i << " ";}
int main()
{
	int first[5] = {10, 20, 30, 80};
	int second[5] = {20, 40, 80, 90, 100};
	vector<int> v(10);
	vector<int>::iterator it;

	sort(first, first+5);
	sort(second, second+5);
	it = set_intersection(first, first+5, second, second+5, v.begin());
	v.resize(it-v.begin());
	for_each(v.begin(), v.end(), my_print);


	system("pause");
	return 0;
}

 
