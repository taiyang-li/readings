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
	int arr[5]= {1,2,3,4,5};
	vector<int> arr1(arr, arr+5);
	
	arr1.resize(10, 100);
	for_each(arr1.begin(), arr1.end(), my_print);
	cout << endl;

	arr1.resize(5);
	for_each(arr1.begin(), arr1.end(), my_print);
	cout << endl;
		
	system("pause");
	return 0;
}

 
