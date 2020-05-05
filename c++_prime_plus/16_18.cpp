#include <iostream>
#include <cstdlib>
#include <string>
#include <cstdio>
#include <algorithm>
#include <list> 
using namespace std;

const int LIM = 10;
void my_print(int i) {cout << i << " ";}
int main()
{	
	int ar[LIM] = {4,5,4,2,2,3,4,8,1,4};
	list<int> la(ar, ar+LIM);
	list<int> lb(la);
	
	cout << "original list contents" << endl;;
	for_each(la.begin(), la.end(), my_print);
	cout << endl;

	la.remove(4);
	
	cout << "after using the remove() method" << endl;
	for_each(la.begin(), la.end(), my_print);
	cout << endl;
	
	list<int>::iterator last;
	last = remove(lb.begin(), lb.end(), 4);
	 
	cout << "after using the remove() method" << endl ;
	for_each(lb.begin(), lb.end(), my_print);
	cout << endl;

	// 删除尾部 
	lb.erase(last, lb.end());


	cout << "after using the erase() method" << endl;
	for_each(lb.begin(), lb.end(), my_print);
	cout << endl;

	
	

	system("pause");
	return 0;
}

 
